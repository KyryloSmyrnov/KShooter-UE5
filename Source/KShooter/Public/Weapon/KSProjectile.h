// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/KSBaseWeaponFXComponent.h"
#include "GameFramework/Actor.h"
#include "KSProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UKSBaseWeaponFXComponent;

UCLASS()
class KSHOOTER_API AKSProjectile : public AActor
{
    GENERATED_BODY()

public:
    AKSProjectile();

    void SetShotDirection(const FVector Direction) { ShotDirection = Direction; }

protected:
    UPROPERTY(VisibleAnywhere, Category="Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category="Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, Category="VFX")
    UKSBaseWeaponFXComponent* ProjectileFXComponent;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageRadius = 200.0f;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageAmount = 50.0f;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    bool DoFullDamage = false;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float LifeSeconds = 5.0f;

    virtual void BeginPlay() override;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

    AController* GetController() const;
};
