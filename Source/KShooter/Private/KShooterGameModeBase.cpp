// KShooter - All Rights Reserved

#include "KShooterGameModeBase.h"
#include "KSBaseCharacter.h"
#include "KSPlayerController.h"
#include "UI/KSGameHUD.h"

AKShooterGameModeBase::AKShooterGameModeBase()
{
    DefaultPawnClass = AKSBaseCharacter::StaticClass();
    PlayerControllerClass = AKSPlayerController::StaticClass();
    HUDClass = AKSGameHUD::StaticClass();
}
