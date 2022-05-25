// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KSBaseWeapon.h"
#include "KSRifleWeapon.generated.h"

class UKSBaseWeaponFXComponent;

UCLASS()
class KSHOOTER_API AKSRifleWeapon : public AKSBaseWeapon
{
    GENERATED_BODY()

public:
    AKSRifleWeapon();
    
    virtual void StartShoot() override;
    virtual void StopShoot() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float ShotFrequency = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageAmount = 15.0f;

    UPROPERTY(VisibleAnywhere, Category="VFX")
    UKSBaseWeaponFXComponent* RifleFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;
    
    void MakeDamage(const FHitResult& HitResult);
};
