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
