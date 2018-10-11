// Copyright 2018 Project Flashpoint. All rights reserved!

#include "Weapon.h"


// Sets default values
AWeapon::AWeapon() {
	meshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	meshWeapon->bCastDynamicShadow = false;
	meshWeapon->CastShadow = false;


	weaponMuzzleLocation = CreateDefaultSubobject<USceneComponent>(
		TEXT("MuzzleLocation"));
	weaponMuzzleLocation->SetupAttachment(meshWeapon);
	weaponMuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	UE_LOG(LogTemp, Warning, TEXT("Gun created"));

}



// Called when the game starts or when spawned
void AWeapon::BeginPlay() {
	Super::BeginPlay();
	
}

void AWeapon::OnFire() {
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}