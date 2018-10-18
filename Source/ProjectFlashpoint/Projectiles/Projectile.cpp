// Copyright 2018 Project Flashpoint. All rights reserved!

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile() {
	collisionComponent = CreateDefaultSubobject<USphereComponent>(
		TEXT("collisionComponent")
	);
	collisionComponent->InitSphereRadius(collisionRadius);
	collisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	
	// set up a notification for when this component hits something blocking
	collisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	// Set as root component
	RootComponent = collisionComponent;


	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("projectileMovement"));
	projectileMovement->UpdatedComponent = collisionComponent;
	projectileMovement->InitialSpeed = 3000.f;
	projectileMovement->MaxSpeed = 3000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();
	
}

void AProjectile::OnHit(UPrimitiveComponent * hitComp, AActor * otherActor,
	UPrimitiveComponent * otherComp, FVector normalImpulse,
	const FHitResult & hit) {

	if((otherActor != NULL) && (otherActor != this) && (otherComp != NULL) &&
		otherComp->IsSimulatingPhysics()) {
		otherComp->AddImpulseAtLocation(GetVelocity() * 100.0f,
			GetActorLocation());
	}
	Destroy();
}
