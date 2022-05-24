// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "KSProjectile.h"
#include "Weapon/KSBaseWeapon.h"
#include "KSLauncherWeapon.generated.h"

class AKSProjectile;

UCLASS()
class KSHOOTER_API AKSLauncherWeapon : public AKSBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartShoot() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<AKSProjectile> ProjectileClass;
    
    virtual void MakeShot() override;
};
