// Copyright 2018 Project Flashpoint. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "TimerManager.h"
#include "../Projectiles/Projectile.h"
#include "../Soldiers/Soldier.h"
#include <typeinfo>
#include "FireComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponMode: uint8{
    WM_SingleFire     UMETA(DisplayName = "SingleFire"),
    WM_BurstFire      UMETA(DisplayName = "BurstFire"),
    WM_FullAuto       UMETA(DisplayName = "FullAutomaticFire"),
    WM_Shotgun        UMETA(DisplayName = "Shotgun")
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFLASHPOINT_API UFireComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireComponent();

	// Sets the hipFireLocation - UNUSED 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector hipFireLocation;

	// SEt the adsFireLocation - UNUSED
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector adsFireLocation;

	// Sets the damage of each bullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float damage = 10.0f;

	// Set the rate of fire for the component. Rounds per Minute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int rateOfFire = 780;

	// Sets the vertical recoil ratio. 0-1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float verticalRecoil = .1f;

    // Sets the vertical recoil ratio. 0-1
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float minVerticalRecoil = .0f;

	// Sets the horizontal recoil ratio. 0-1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float horizontalRecoil = .1f;

	// Sets the max ammo reserves
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int maxAmmoReserves = 530;

	// Sets the max magazine size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int maxMagazineSize = 30;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int pelletsPerShell = 6;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float pelletSpread = 10.f;

	// Sets the weapon to single fire capable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Mode")
	bool bSingleFireMode = true;

	// Sets the weapon to burst fire capable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Mode")
	bool bBurstFireMode = true;

	// Sets the weapon to full auto fire capable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Mode")
	bool bFullAutoMode = true;

    // Sets the weapon to use shotgun fire logic
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Mode")
    bool bShotgunMode = false;

	// Sets the rounds per burst for burst auto capable weapions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Mode")
	int shotsPerBurst = 3;

	// Select fire weapon component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Mode")
	EWeaponMode fireMode = EWeaponMode::WM_SingleFire;

	// Defires the projectile to shoot
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> projectileClass;
    
	/** Gets the current magazine size
	 * @param int - Current magazine size
	*/
    UFUNCTION(BlueprintCallable, Category = "Status")
    int getCurrentMagazineSize() const;

	/** Gets the current magazine size
	 * @param int - Current magazine size
	*/
	UFUNCTION(BlueprintCallable, Category = "Status")
	int getCurrentAmmoReserves() const;

	/** Fires the weapon based on the current mode selected
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnFire();

	/** Used to stop full auto mode when the tigger is released
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnRelease();

	/** Toggles the component between the acceptable fire components
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ToggleFireMode();

	/** Reloads the weapon based on magazine size and ammo reserves
	*/
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnReload();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every tick when the component is registered to an actor
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	/** Adjusts the aim to the current target view point
	*/
	void adjustAim();

private:
	int currentMagazineSize = maxMagazineSize;
	int currentAmmoReserves = maxAmmoReserves;

	bool burstShooting = false;
	bool canFire = true;

	float lastShotTime = 0;
	float nextShotTime = 0;
	int currentShot = 0;

	FTimerHandle fullAutoTimer;

	/** Controls the burst logic
	*/
	void fireBurst();
	/** Controls the full auto logic
	*/
	void fireFull();
	/** Controls the single fire logic
	*/
	void fireSingle();
    /** Controls the shotgun fire logic
    */
    void fireShotgun();

	/** Fires the bullet 
	*/
	void shootBullet();
    /** Fires shotgun bullet
    */
    void shootShotgun();

    void addRecoilToSoldier();

	/** Get the seconds between shots
	 * @param flaot - seconds between each shot
	*/
	float getSecondsPerShot();

	/** Sets the state to can fire again
	*/
	void canFireAgain();
};
