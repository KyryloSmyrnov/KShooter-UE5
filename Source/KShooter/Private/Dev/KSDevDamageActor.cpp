// KShooter - All Rights Reserved

#include "Dev/KSDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

//REMOVE LATER

AKSDevDamageActor::AKSDevDamageActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}


void AKSDevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}


void AKSDevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

    UGameplayStatics::ApplyRadialDamage(
        GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}
