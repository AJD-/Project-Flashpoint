// Copyright 2018 Project Flashpoint. All rights reserved!

#include "FireComponent.h"
#include <typeinfo>

// Sets default values for this component's properties
UFireComponent::UFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}




// Called when the game starts
void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

    currentMagazineSize = maxMagazineSize;
    currentAmmoReserves = maxAmmoReserves;

	// Sets priority to Full, Burst, Single on multi fire mode weapons.
    if(bShotgunMode) {
        fireMode = EWeaponMode::WM_Shotgun;
    } else if(bFullAutoMode) {
		fireMode = EWeaponMode::WM_FullAuto;
	} else if(bBurstFireMode) {
		fireMode = EWeaponMode::WM_BurstFire;
	} else {
		fireMode = EWeaponMode::WM_SingleFire;
	}
}

void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction * ThisTickFunction) {
	// Burst Fire Logic
	if(burstShooting) {
		lastShotTime += DeltaTime;
		if(nextShotTime <= lastShotTime) {
			fireBurst();
		}
	}
}

void UFireComponent::adjustAim() {
	// Get the Soldiers camera location and rotation.
	ASoldier* soldier;
	try {
		soldier = ((ASoldier*) GetOwner());
	} catch (std::bad_cast& bc) {
		bc.what();
		UE_LOG(LogTemp, Error, TEXT("Attempting to cast non-Soldier to Soldier"));
		return;
	}

	FVector viewPointLocationStart = soldier->firstPersonCameraComponent->
		GetComponentLocation();
	FRotator viewPointRotation = soldier->firstPersonCameraComponent->
		GetComponentRotation();

	// Find the end of the view point
	FVector viewPointLocationEnd = viewPointLocationStart +
		viewPointRotation.Vector() * soldier->maxEngagementLine;

	// Get direction to shoot in
	FRotator direction = (viewPointLocationEnd - this->GetComponentLocation())
		.Rotation();

	// Make this the fire direction
	this->AddRelativeRotation(direction);
}

int UFireComponent::getCurrentMagazineSize() const{
    return currentMagazineSize;
}

int UFireComponent::getCurrentAmmoReserves() const {
	return currentAmmoReserves;
}

void UFireComponent::OnFire() {
	// If already firing
	if(!canFire) {
		return;
	}
	switch(fireMode) {
	case EWeaponMode::WM_BurstFire:
		canFire = false;
		fireBurst();
		break;
	case EWeaponMode::WM_FullAuto:
		fireFull();
		break;
	case EWeaponMode::WM_SingleFire:
		canFire = false;
		fireSingle();
		break;
    case EWeaponMode::WM_Shotgun:
        canFire = false;
        fireShotgun();
        break;
	}
}

void UFireComponent::OnRelease() {
	GetWorld()->GetTimerManager().ClearTimer(fullAutoTimer);
}

void UFireComponent::ToggleFireMode() {
	// For each mode, toggle to the next. If that mode is not available, 
	//  contine to toggle
	switch(fireMode) {
	case EWeaponMode::WM_SingleFire:
		fireMode = EWeaponMode::WM_BurstFire;
		if(!bBurstFireMode) {
			ToggleFireMode();
		}
		break;
	case EWeaponMode::WM_BurstFire:
		fireMode = EWeaponMode::WM_FullAuto;
		if(!bFullAutoMode) {
			ToggleFireMode();
		}
		break;
	case EWeaponMode::WM_FullAuto:
		fireMode = EWeaponMode::WM_SingleFire;
		if(!bSingleFireMode) {
			ToggleFireMode();
		}
		break;
	}
}

void UFireComponent::OnReload() {

	//if have no ammo left or the magazine is full, can't reload
	if(currentAmmoReserves <= 0 || currentMagazineSize >= maxMagazineSize) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to Reload"));
		return;
	}

	//if have less bullets in reserves then the magazine size
	//fill the magazine with whatever is left
	if(currentAmmoReserves < (maxMagazineSize - currentMagazineSize)) {
		currentMagazineSize = currentMagazineSize + currentAmmoReserves;
		currentAmmoReserves = 0;

	}
	//fill up magazine with ammo
	else {
		currentAmmoReserves -= (maxMagazineSize - currentMagazineSize);
		currentMagazineSize = maxMagazineSize;
	}
}

void UFireComponent::spawnProjectile(FTransform transform) {
    //Set Spawn Collision Handling Override
    FActorSpawnParameters spawnParams;
    spawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::
        AlwaysSpawn;

    // spawn the projectile at the muzzle
    AProjectile* spawnedProjectile = GetWorld()->
        SpawnActor<AProjectile>(projectileClass, transform,
            spawnParams);

    spawnedProjectile->projectileDamage = damage;
}

void UFireComponent::spawnProjectileMulticast_Implementation(
    FTransform transform) {
    spawnProjectile(transform);
}

bool UFireComponent::spawnProjectileMulticast_Validate(
    FTransform transform) {
    return true;
}

void UFireComponent::spawnProjectileServer_Implementation(
    FTransform transform) {
    spawnProjectileMulticast(transform);
}

bool UFireComponent::spawnProjectileServer_Validate(
    FTransform transform) {
    return true;
}

void UFireComponent::fireBurst() {
	// If burst still firing
	if(currentShot < shotsPerBurst) {
		burstShooting = true;
		shootBullet();

		// Get the last and next shot time
		lastShotTime = GetWorld()->GetTimeSeconds();
		nextShotTime = lastShotTime + getSecondsPerShot();

		currentShot++;
	// If the burst is over. Reset state
	} else {
		burstShooting = false;
		canFire = true;
		currentShot = 0;
	}
}

void UFireComponent::fireFull() {
	shootBullet();

	// Continuously fire until the the timer is cleared
	GetWorld()->GetTimerManager().SetTimer(fullAutoTimer, this,
		&UFireComponent::shootBullet, getSecondsPerShot(), true);
}

void UFireComponent::fireSingle() {
	shootBullet();
	
	// Unused timer handle
	FTimerHandle UNUSED;
	// Call the can fire funciton after a set time
	GetWorld()->GetTimerManager().SetTimer(UNUSED, this,
		&UFireComponent::canFireAgain, getSecondsPerShot(), false);
}

void UFireComponent::fireShotgun() {
    shootShotgun();

    // Unused timer handle
    FTimerHandle UNUSED;
    // Call the can fire funciton after a set time
    GetWorld()->GetTimerManager().SetTimer(UNUSED, this,
        &UFireComponent::canFireAgain, getSecondsPerShot(), false);
}

void UFireComponent::shootBullet() {
	if(projectileClass != NULL) {
		if(GetWorld() != NULL) {

            //if have no ammo can't fire
            if(currentMagazineSize <= 0){
                UE_LOG(LogTemp, Warning, TEXT("Out of Ammo"));
                return;
            }

            //decrement ammo
            currentMagazineSize -= 1;

            FTransform transfrom = GetComponentToWorld();

            spawnProjectileServer(transfrom);

            addRecoilToSoldier();
		}
	}
}

void UFireComponent::shootShotgun() {
    if(projectileClass != NULL) {
        if(GetWorld() != NULL) {

            //if have no ammo can't fire
            if(currentMagazineSize <= 0) {
                UE_LOG(LogTemp, Warning, TEXT("Out of Ammo"));
                return;
            }

            //decrement ammo
            currentMagazineSize -= 1;


            //Set Spawn Collision Handling Override
            FActorSpawnParameters spawnParams;
            spawnParams.SpawnCollisionHandlingOverride =
                ESpawnActorCollisionHandlingMethod::
                AlwaysSpawn;

            for(int i = 0; i < pelletsPerShell; i++) {

                FTransform spawnTransform = GetComponentToWorld();
                // One pellet will always go directly straight
                if(i != 0) {
                    float randomPitch = FMath::RandRange(-1.f, 1.f)
                        *pelletSpread;
                    float randomYaw = FMath::RandRange(-1.f, 1.f)
                        *pelletSpread;

                    FRotator newRotation(randomPitch, randomYaw, 0);
                    FRotator invRotation(-randomPitch, -randomYaw, 0);
                    AddRelativeRotation(newRotation);
                    spawnTransform = GetComponentToWorld();
                    AddRelativeRotation(invRotation);
                }


                spawnProjectileServer(spawnTransform);
            }

            addRecoilToSoldier();
        }
    }
}

void UFireComponent::addRecoilToSoldier() {
    // Apply Recoil
    ASoldier* soldier;
    try {
        soldier = ((ASoldier*) GetOwner());
    } catch(std::bad_cast& bc) {
        bc.what();
        UE_LOG(LogTemp, Error, TEXT("Attempting to cast non-Soldier to Soldier"));
        return;
    }

    float vertical = 0.0;
    if(verticalRecoil != 0) {
        float max = -1.f + minVerticalRecoil / verticalRecoil;
        vertical = (FMath::RandRange(max, 0.f)*verticalRecoil) 
            +- minVerticalRecoil;
    }
    float horizontal = FMath::RandRange(-1.f, 1.f)*horizontalRecoil;
    soldier->AddRecoil(vertical, horizontal);
}

float UFireComponent::getSecondsPerShot() {
	// Calculates the shots per second
	return 60.f/(float)rateOfFire;
}

void UFireComponent::canFireAgain() {
	canFire = true;
}
