// Copyright 2018 Project Flashpoint. All rights reserved!

#include "SoldierAIController.h"
#include "../Soldiers/Soldier.h"

void ASoldierAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ASoldierAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedSoldier = Cast<ASoldier>(InPawn);
		if (!PossessedSoldier) { return; }

	}
}