// Copyright 2018 Project Flashpoint. All rights reserved!

#include "BaseAbility.h"


// Sets default values for this component's properties
UBaseAbility::UBaseAbility()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBaseAbility::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBaseAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseAbility::executeAbilityMulticast_Implementation() {
    UE_LOG(LogTemp, Warning, TEXT("Multicast Impl"));
    executeAbility();
}

bool UBaseAbility::executeAbilityMulticast_Validate() {
    return true;
}

void UBaseAbility::executeAbilityServer_Implementation() {
    UE_LOG(LogTemp, Warning, TEXT("Server Impl"));
    executeAbilityMulticast();
}

bool UBaseAbility::executeAbilityServer_Validate() {
    return true;
}

void UBaseAbility::useAbility() {
    executeAbilityServer();
}
