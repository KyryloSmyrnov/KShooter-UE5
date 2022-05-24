// KShooter - All Rights Reserved

#include "Components/KSHealthComponent.h"
#include "Dev/KSFireDamageType.h"
#include "Dev/KSIceDamageType.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UKSHealthComponent::UKSHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UKSHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);
    AActor* ComponentOwner = GetOwner();

    if (ComponentOwner)
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UKSHealthComponent::OnTakeAnyDamage);
}

void UKSHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;

    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
        OnDeath.Broadcast();
    else if (AutoHeal)
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UKSHealthComponent::HealUpdate, HealFrequence, true, HealDelay);
}

void UKSHealthComponent::HealUpdate()
{
    SetHealth(Health + HealCount);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
}

void UKSHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
