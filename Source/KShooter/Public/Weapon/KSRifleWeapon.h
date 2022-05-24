// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KSBaseWeapon.h"
#include "KSRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KSHOOTER_API AKSRifleWeapon : public AKSBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartShoot() override;
    virtual void StopShoot() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float ShotFrequency = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 15.0f;


    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;
    
    void MakeDamage(const FHitResult& HitResult);
};
