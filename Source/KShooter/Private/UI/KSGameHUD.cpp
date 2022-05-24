// KShooter - All Rights Reserved

#include "UI/KSGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void AKSGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void AKSGameHUD::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    
    if(PlayerHUDWidget)
        PlayerHUDWidget->AddToViewport();
    
}

