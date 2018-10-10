// Copyright 2018 Project Flashpoint. All rights reserved!

#include "Soldier.h"


// Sets default values
ASoldier::ASoldier()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(
		TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());

	// Position the camera
	firstPersonCameraComponent->RelativeLocation =
		FVector(-39.56f, 1.75f, 64.f);
	firstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a 
	//  '1st person' view (when controlling this pawn)
	meshSoldier = CreateDefaultSubobject<USkeletalMeshComponent>(
		TEXT("CharacterMesh1P"));
	meshSoldier->SetOnlyOwnerSee(true);
	meshSoldier->SetupAttachment(firstPersonCameraComponent);
	meshSoldier->bCastDynamicShadow = false;
	meshSoldier->CastShadow = false;
	meshSoldier->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	meshSoldier->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void ASoldier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

