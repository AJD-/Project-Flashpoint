// Copyright 2018 Project Flashpoint. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECTFLASHPOINT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* meshWeapon;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* weaponMuzzleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* fireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* fireAnimation;

	// Sets default values for this actor's properties
	AWeapon();


	// Fires a single projectile. handle rapid fire in blueprint
	UFUNCTION(BlueprintCallable, Category = "Input")
	void onShoot();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void onReload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//int currentAmmoReserves = maxAmmoReserves;
	//int currentMagazineSize = maxMagazineSize;
};