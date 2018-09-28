// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectFlashpointGameMode.h"
#include "ProjectFlashpointHUD.h"
#include "ProjectFlashpointCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectFlashpointGameMode::AProjectFlashpointGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectFlashpointHUD::StaticClass();
}
