// KShooter - All Rights Reserved

#include "Weapon/KSLauncherWeapon.h"
#include "Weapon/KSProjectile.h"

void AKSLauncherWeapon::StartShoot()
{
    MakeShot();
}

void AKSLauncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
        return;

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;

    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetBarrelWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetBarrelWorldLocation());
    AKSProjectile* Projectile = GetWorld()->SpawnActorDeferred<AKSProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
}
