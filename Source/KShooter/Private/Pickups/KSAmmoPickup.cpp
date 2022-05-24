// KShooter - All Rights Reserved

#include "Pickups/KSAmmoPickup.h"
#include "Components/KSWeaponComponent.h"
#include "Components/KSHealthComponent.h"
#include "KSUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AKSAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{

    const auto HealthComponent = KSUtils::GetKSPlayerComponent<UKSHealthComponent>(PlayerPawn);
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = KSUtils::GetKSPlayerComponent<UKSWeaponComponent>(PlayerPawn);
    if(!WeaponComponent) return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
