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

		//// Subscribe our local method to the tank's death event
		//PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ASoldierAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerSoldier = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledSoldier = GetPawn();

	if (!(PlayerSoldier && ControlledSoldier)) { return; }

	UE_LOG(LogTemp, Warning, TEXT("AI Woop Woop"));

	// Move towards the player
	MoveToActor(PlayerSoldier, AcceptanceRadius); // TODO check radius is in cm

	//// Aim towards the player
	//auto AimingComponent = ControlledSoldier->FindComponentByClass<UTankAimingComponent>();
	//AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//if (AimingComponent->GetFiringState() == EFiringState::Locked)
	//{
	//	AimingComponent->Fire(); // TODO limit firing rate
	//}
}
