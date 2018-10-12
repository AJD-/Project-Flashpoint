// Copyright 2018 Project Flashpoint. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "../Projectiles/Projectile.h"
#include "FireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFLASHPOINT_API UFireComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
		FVector hipFireLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
		FVector adsFireLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int rateOfFire = 780;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float verticalRecoil = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float horizontalRecoil = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int maxAmmoReserves = 560;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int maxMagazineSize = 30;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> projectileClass;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnShoot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int currentMagazineSize = maxMagazineSize;
	int currentAmmoReserves = maxAmmoReserves;
};
