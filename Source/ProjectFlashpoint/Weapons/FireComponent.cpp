// Copyright 2018 Project Flashpoint. All rights reserved!

#include <typeinfo>
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

	adjustAim();
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

void UFireComponent::OnShoot() {
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));

	if(projectileClass != NULL) {
		if(GetWorld() != NULL) {

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