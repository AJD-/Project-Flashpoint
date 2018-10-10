// Copywrite 2018 Project Flashpoint. All rights reserved.

#include "ProjectFlashpointGameMode.h"
#include "ProjectFlashpointHUD.h"
#include "ProjectFlashpointCharacter.h"
#include "UObject/ConstructorHelpers.h"


AProjectFlashpointGameMode::AProjectFlashpointGameMode()
	: Super() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/Dynamic/Soldiers/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectFlashpointHUD::StaticClass();
}
