// KShooter - All Rights Reserved


#include "UI/KSPlayerHudWidget.h"
#include "Components/KSHealthComponent.h"
#include "Components/KSWeaponComponent.h"
#include "KSUtils.h"

float UKSPlayerHudWidget::GetHealthPercent() const
{
    const auto HealthComponent = KSUtils::GetKSPlayerComponent<UKSHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent)
        return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UKSPlayerHudWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = KSUtils::GetKSPlayerComponent<UKSWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UKSPlayerHudWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = KSUtils::GetKSPlayerComponent<UKSWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UKSPlayerHudWidget::IsPlayerAlive() const
{
    const auto HealthComponent = KSUtils::GetKSPlayerComponent<UKSHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool UKSPlayerHudWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return  Controller && Controller->GetStateName() == NAME_Spectating;
}