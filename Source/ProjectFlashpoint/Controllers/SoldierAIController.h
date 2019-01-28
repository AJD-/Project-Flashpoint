// Copyright 2018 Project Flashpoint. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoldierAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFLASHPOINT_API ASoldierAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// How close can the AI Soldiers get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 0;

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	//UFUNCTION()
	//	void OnPossedTankDeath();
	
	
};
