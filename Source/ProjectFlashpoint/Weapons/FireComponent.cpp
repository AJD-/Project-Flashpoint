// Copyright 2018 Project Flashpoint. All rights reserved!

#include "FireComponent.h"


// Sets default values for this component's properties
UFireComponent::UFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFireComponent::OnShoot() {
	if(projectileClass != NULL) {
		if(GetWorld() != NULL) {
            
            //if have no ammo can't fire
            if(currentMagazineSize <= 0){
                UE_LOG(LogTemp, Warning, TEXT("Out of Ammo"));
                return;
            }
            UE_LOG(LogTemp, Warning, TEXT("Shooting-Current Ammo: %d"),currentMagazineSize );
            
            //decrement ammo
            currentMagazineSize -= 1;
            
			FTransform spawnTransform = GetComponentToWorld();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::
				AlwaysSpawn;
			
			// spawn the projectile at the muzzle
			AProjectile* spawnedProjectile = GetWorld()->
				SpawnActor<AProjectile>(projectileClass, spawnTransform, 
					spawnParams);
			
			spawnedProjectile->projectileDamage = damage;
		}
	}
}

void UFireComponent::OnReload() {
    //UE_LOG(LogTemp, Warning, TEXT("Reload"));
    
    //if have no ammo left or the magazine is full, can't reload
    if(currentAmmoReserves <= 0 || currentMagazineSize >= 30){
        UE_LOG(LogTemp, Warning, TEXT("Unable to Reload"));
        return;
    }
    
    //if have less bullets in reserves then the magazine size
    //fill the magazine with whatever is left
    if(currentAmmoReserves < (maxMagazineSize - currentMagazineSize)){
        UE_LOG(LogTemp, Warning, TEXT("Reloading-CurrentReserves: %d"),currentAmmoReserves);
        currentMagazineSize = currentMagazineSize + currentAmmoReserves;
        currentAmmoReserves = 0;
        UE_LOG(LogTemp, Warning, TEXT("Reloaded-CurrentReserves: %d"),currentAmmoReserves);
        
    }
    //fill up magazine with ammo
    else{
        currentAmmoReserves -= (maxMagazineSize -  currentMagazineSize);
        currentMagazineSize = maxMagazineSize;
        UE_LOG(LogTemp, Warning, TEXT("Reloaded-CurrentReserves: %d"),currentAmmoReserves);
    }
    
}
