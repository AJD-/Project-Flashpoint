// Copyright 2018 Project Flashpoint. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECTFLASHPOINT_API AProjectile : public AActor
{
	GENERATED_BODY()
	

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* collisionComponent;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float collisionRadius = 4.0f;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = 
		(AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* projectileMovement;

	float projectileDamage = 0.0f;

public:
	// Sets default values for this actor's properties
	AProjectile();

	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() 
		const { 
		return projectileMovement; 
	}

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
		const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
