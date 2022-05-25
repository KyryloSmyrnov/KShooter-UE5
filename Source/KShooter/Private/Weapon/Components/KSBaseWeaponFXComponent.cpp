// KShooter - All Rights Reserved


#include "Weapon/Components/KSBaseWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UKSBaseWeaponFXComponent::UKSBaseWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UKSBaseWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    auto Effect = DefaultEffect;

    if(Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if(EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
