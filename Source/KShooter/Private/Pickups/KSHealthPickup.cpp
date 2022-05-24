// KShooter - All Rights Reserved

#include "Pickups/KSHealthPickup.h"
#include "Components/KSHealthComponent.h"
#include "KSUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AKSHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = KSUtils::GetKSPlayerComponent<UKSHealthComponent>(PlayerPawn);
    if(!HealthComponent) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}
