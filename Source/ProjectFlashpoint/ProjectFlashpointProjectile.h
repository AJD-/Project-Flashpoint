// Copywrite 2018 Project Flashpoint. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectFlashpointProjectile.generated.h"

UCLASS(config=Game)
/** Projectile fired form the gun
*/
class AProjectFlashpointProjectile : public AActor
{
	GENERATED_BODY()

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = 
		(AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	AProjectFlashpointProjectile();

	// called when projectile hits something
	UFUNCTION()
	void onHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
		const FHitResult& Hit);

	// Returns CollisionComp subobject
	FORCEINLINE class USphereComponent* getCollisionComp() const {
		return CollisionComp;
	}
	// Returns ProjectileMovement subobject
	FORCEINLINE class UProjectileMovementComponent* getProjectileMovement() 
		const { 
		return ProjectileMovement; 
	}
};

