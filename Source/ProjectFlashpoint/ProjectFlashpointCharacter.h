// Copywrite 2018 Project Flashpoint. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectFlashpointCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
/** Player controlled character for Project Flashpoint. Contains a gun and the
 *  first-person camera. Handles input to control there character
*/
class AProjectFlashpointCharacter : public ACharacter
{
	GENERATED_BODY()

	// Pawn mesh: 1st person view (arms; seen only by self) 
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	// Gun mesh: 1st person view (seen only by self)
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	// Location on gun mesh where projectiles should spawn. 
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, 
	 * just the actual gun) 
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	// Location on VR gun mesh where projectiles should spawn. 
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	// First person camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = 
		(AllowPrivateAccess = "true")
	)
	class UCameraComponent* FirstPersonCameraComponent;

	// Motion controller (right hand) 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = 
		(AllowPrivateAccess = "true")
	)
	class UMotionControllerComponent* R_MotionController;

	// Motion controller (left hand) 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = 
		(AllowPrivateAccess = "true")
	)
	class UMotionControllerComponent* L_MotionController;

public:
	AProjectFlashpointCharacter();

	// Base turn rate, in deg/sec. Other scaling may affect final turn rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	// Base look up/down rate, in deg/sec. Other scaling may affect final rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// Gun muzzle's offset from the characters location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectFlashpointProjectile> ProjectileClass;

	// Sound to play each time we fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	// AnimMontage to play each time we fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	// Whether to use motion controller location for aiming.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		uint32 bUsingMotionControllers : 1;

	// Returns Mesh1P subobject
	FORCEINLINE class USkeletalMeshComponent* getMesh1P() const 
	{ return Mesh1P; }

	// Returns FirstPersonCameraComponent subobject
	FORCEINLINE class UCameraComponent* getFirstPersonCameraComponent() 
		const { return FirstPersonCameraComponent; }


protected:
	virtual void BeginPlay();
	
	// Fires a projectile.
	void onFire();

	// Resets HMD orientation and position in VR.
	void onResetVR();

	// Handles moving forward/backward
	void moveForward(float val);

	// Handles stafing movement, left and right
	void moveRight(float val);

	/**
	 * Called via input to turn at a given rate.
	 * @param rate:float -	 This is a normalized rate, i.e. 1.0 means 100%
	 */
	void turnAtRate(float rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param rate:float - This is a normalized rate, i.e. 1.0 means 100%
	 */
	void lookUpAtRate(float rate);

	struct TouchData
	{
		TouchData() { isPressed = false; location=FVector::ZeroVector;}
		bool isPressed;
		ETouchIndex::Type FingerIndex;
		FVector location;
		bool bMoved;
	};
	void beginTouch(const ETouchIndex::Type fingerIndex, 
		const FVector location);
	void endTouch(const ETouchIndex::Type fingerIndex, const FVector location);
	void touchUpdate(const ETouchIndex::Type fingerIndex, 
		const FVector location);
	TouchData TouchItem;

	/** Sets up the player input controls
	 *
	 * @param inputComponent:UInputComponent - The input component pointer to
	 *		bind controls to
	*/
	virtual void SetupPlayerInputComponent(UInputComponent* inputComponent) 
		override;

	/* 
	 * Configures input for touchscreen devices if there is a valid touch 
	 *  interface for doing so 
	 *
	 * @param inputComponent:UInputComponent - The input component pointer to 
	 *		bind controls to
	 * @returns bool - true if touch controls were enabled.
	 */
	bool enableTouchscreenMovement(UInputComponent* inputComponent);
};

