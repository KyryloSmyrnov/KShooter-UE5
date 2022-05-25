// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KSBaseWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KSHOOTER_API UKSBaseWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UKSBaseWeaponFXComponent();

    void PlayImpactFX(const FHitResult& Hit);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    UNiagaraSystem* DefaultEffect;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;
};
