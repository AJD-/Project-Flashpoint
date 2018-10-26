// Copyright 2018 Project Flashpoint. All rights reserved!

#include "Soldier.h"


// Sets default values
ASoldier::ASoldier() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(32.5f, 90.0f);

	meshSoldier = GetMesh();
	meshSoldier->SetRelativeLocation(FVector(0.0f, -5.0f, -90.0f));
	meshSoldier->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));


/******************** First Person Orientation Setup ****************************/
	// Create a CameraComponent	
	firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(
		TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());

	// Position the camera
	firstPersonCameraComponent->RelativeLocation =
		FVector(-39.5f, 1.75f, 64.f);
	firstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a 
	//  '1st person' view (when controlling this pawn)
	firstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(
		TEXT("FirstPersonMeshComponent"));
	firstPersonMeshComponent->SetOnlyOwnerSee(true);
	firstPersonMeshComponent->SetupAttachment(firstPersonCameraComponent);
	firstPersonMeshComponent->bCastDynamicShadow = false;
	firstPersonMeshComponent->CastShadow = false;
	firstPersonMeshComponent->SetRelativeLocation(
		FVector(-0.5f, -4.4f, -155.7f)
	);
	firstPersonMeshComponent->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2));
}

// Called when the game starts or when spawned
void ASoldier::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ASoldier::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASoldier::SetupPlayerInputComponent(
	UInputComponent* playerInputComponent) {
	// set up gameplay key bindings
	check(playerInputComponent);

	//// Bind jump events
	//playerInputComponent->BindAction("Jump", IE_Pressed, this,
	//	&ACharacter::Jump);
	//playerInputComponent->BindAction("Jump", IE_Released, this,
	//	&ACharacter::StopJumping);

	// Bind movement events
	playerInputComponent->BindAxis("MoveForward", this,
		&ASoldier::moveForward);
	playerInputComponent->BindAxis("MoveRight", this,
		&ASoldier::moveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	playerInputComponent->BindAxis("Turn", this,
		&APawn::AddControllerYawInput);
	playerInputComponent->BindAxis("TurnRate", this,
		&ASoldier::turnAtRate);
	playerInputComponent->BindAxis("LookUp", this,
		&APawn::AddControllerPitchInput);
	playerInputComponent->BindAxis("LookUpRate", this,
		&ASoldier::lookUpAtRate);

}

void ASoldier::moveForward(float value) {
	if(value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ASoldier::moveRight(float value) {
	if(value != 0.0f) {
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ASoldier::turnAtRate(float rate) {
	AddControllerYawInput(rate * baseLookUpRate * 
		GetWorld()->GetDeltaSeconds()
	);
}

void ASoldier::lookUpAtRate(float rate) {
	AddControllerPitchInput(rate * baseLookUpRate *
		GetWorld()->GetDeltaSeconds()
	);
}