// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KSBasePickups.h"
#include "KSHealthPickup.generated.h"

UCLASS()
class KSHOOTER_API AKSHealthPickup : public AKSBasePickups
{
    GENERATED_BODY()
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin = "1.0", ClampMax = "100.0"))
    float HealthAmount = 100.0f;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
