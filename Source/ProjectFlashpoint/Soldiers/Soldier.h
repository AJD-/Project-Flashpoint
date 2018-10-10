// Copyright 2018 Project Flashpoint. All rights reserved!

/** Creates a base class for all soldiers in Project Flashpoint. Handles movement,
 *   input, and other default properties that will be used by all other soldiers.
 *
 * @author Jake Rowland
 * @created 2018-10-10 03:09:32
*/

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Soldier.generated.h"

UCLASS()
class PROJECTFLASHPOINT_API ASoldier : public ACharacter
{
	GENERATED_BODY()

public:

	// Pawn mesh: 1st person view (arms; seen only by self) 
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* meshSoldier;

	// First person camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta =
		(AllowPrivateAccess = "true")
	)
	class UCameraComponent* firstPersonCameraComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> weaponBlueprint;

	// Base turn rate, in deg/sec. Other scaling may affect final turn rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float baseTurnRate = 45.f;

	// Base look up/down rate, in deg/sec. Other scaling may affect final rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float baseLookUpRate = 45.f;

/****************************** Health Properties *******************************/

	// Sets the base armor for the Soldier
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float armor = 20.0;

	// Sets the base health for the Solder
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float health = 100.0;

/****************************** Sight Properties ********************************/

	// Defines how far the Soldier can see in centimeters
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sight")
	float maxSightLine = 10000.0;

	// Defines how far the Soldier can engage in centimeters
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sight")
	float maxEngagementLine = 8500.0;

	// Sets default values for this character's properties
	ASoldier();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* 
		PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
};
