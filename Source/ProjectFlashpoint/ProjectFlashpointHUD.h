// Copywrite 2018 Project Flashpoint. All rights reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectFlashpointHUD.generated.h"

UCLASS()
/** Basic HUD for Project Flashpoint
*/
class AProjectFlashpointHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectFlashpointHUD();

	// Primary draw call for the HUD
	virtual void DrawHUD() override;

private:
	// Crosshair asset pointer
	class UTexture2D* crosshairTex;

};

