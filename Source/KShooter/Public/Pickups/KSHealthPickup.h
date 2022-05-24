// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KSBasePickups.h"
#include "KSHealthPickup.generated.h"

UCLASS()
class KSHOOTER_API AKSHealthPickup : public AKSBasePickups
{
    GENERATED_BODY()

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
