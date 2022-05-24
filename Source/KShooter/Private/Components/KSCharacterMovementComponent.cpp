// KShooter - All Rights Reserved

#include "Components/KSCharacterMovementComponent.h"
#include "KSBaseCharacter.h"

float UKSCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AKSBaseCharacter* Player = Cast<AKSBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}