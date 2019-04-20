// Copyright 2018 Project Flashpoint. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseAbility.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFLASHPOINT_API UBaseAbility : public USceneComponent
{
    GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseAbility();

    UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
    void executeAbility();

    UFUNCTION(Reliable, Server, WithValidation)
        void executeAbilityServer();
    virtual void executeAbilityServer_Implementation();
    virtual bool executeAbilityServer_Validate();

    UFUNCTION(BlueprintCallable, Category = "Ability")
    void useAbility();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
