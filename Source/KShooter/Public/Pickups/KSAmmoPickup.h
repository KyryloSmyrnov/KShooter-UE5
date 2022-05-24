// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KSBasePickups.h"
#include "Weapon/KSBaseWeapon.h"
#include "KSAmmoPickup.generated.h"

class AKSBaseWeapon;

UCLASS()
class KSHOOTER_API AKSAmmoPickup : public AKSBasePickups
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<AKSBaseWeapon> WeaponType;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
