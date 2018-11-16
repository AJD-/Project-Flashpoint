// Copywrite 2018 Project Flashpoint. All rights reserved.

#include "ProjectFlashpointHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AProjectFlashpointHUD::AProjectFlashpointHUD() {
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(
		TEXT("/Game/Static/Textures/HUD/FirstPersonCrosshair"));
	crosshairTex = CrosshairTexObj.Object;
}


void AProjectFlashpointHUD::DrawHUD() {
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture 
	//  aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X - 8.f),
										   (Center.Y- 8.f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, crosshairTex->Resource,
		FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}
