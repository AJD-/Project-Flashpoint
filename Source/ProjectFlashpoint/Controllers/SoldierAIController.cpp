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

void ASoldierAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledSoldier = Cast<ASoldier>(GetPawn());
	if (!ControlledSoldier) { return; }

	UE_LOG(LogTemp, Warning, TEXT("AI Woop Woop"));
	
	//**********************************************************************//

	// This is example AI code, can be deleted whenever
	bool isSwitching = false;
	if (wait >= 200)
	{
		isSwitching = true;
		lastState += 1;
		wait = 0;
	}
	wait += 1;
	if (isSwitching)
	{
		switch (lastState)
		{
		case 1: // go to jog
			value = 1.0f;
			ControlledSoldier->changeActionState(2);
			break;
		case 2: // go to wait
			ControlledSoldier->changeActionState(2);
			value = 0.0f;
			break;
		case 3: // go to crouch
			value = 1.0f;
			ControlledSoldier->changeActionState(3);
			break;
		case 4: // go to wait
			ControlledSoldier->changeActionState(3);
			value = 0.0f;
			break;
		case 5: // go to prone
			value = 1.0f;
			ControlledSoldier->changeActionState(4);
			break;
		case 6: // go to wait
			ControlledSoldier->changeActionState(4);
			value = 0.0f;
			break;
		case 7: // go to walk
			value = 1.0f;
			ControlledSoldier->changeActionState(1);
			break;
		case 8: // go to wait
			direction = direction * -1;
			lastState = 0;
			ControlledSoldier->changeActionState(1);
			value = 0.0f;
			break;
		}
	}

	ControlledSoldier->moveForward(value * direction);
}
