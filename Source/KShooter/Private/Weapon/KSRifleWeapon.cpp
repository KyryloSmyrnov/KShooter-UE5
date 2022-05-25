// KShooter - All Rights Reserved


#include "Weapon/KSRifleWeapon.h"
#include "Weapon/Components/KSBaseWeaponFXComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AKSRifleWeapon::AKSRifleWeapon()
{
    RifleFXComponent = CreateDefaultSubobject<UKSBaseWeaponFXComponent>("RifleFXComponent");
}

void AKSRifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(RifleFXComponent);
}

void AKSRifleWeapon::StartShoot()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AKSRifleWeapon::MakeShot, ShotFrequency, true);
    MakeShot();
}

void AKSRifleWeapon::StopShoot()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}



void AKSRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopShoot();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopShoot();
        return;
    }

    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    CollisionQueryParams.bReturnPhysicalMaterial = true;

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);


    
    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        //DrawDebugLine(GetWorld(), GetBarrelWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::White, false, 5.0f);
        RifleFXComponent->PlayImpactFX(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetBarrelWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
    }

    DecreaseAmmo();
}

bool AKSRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;

    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AKSRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}
