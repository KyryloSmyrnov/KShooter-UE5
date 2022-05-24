// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KSCoreTypes.h"
#include "KSBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class KSHOOTER_API AKSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    AKSBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartShoot();
    virtual void StopShoot();

    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }


    bool TryToAddAmmo(int32 ClipsAmount);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName BarrelSocketName = "BarrelSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;


    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    APlayerController* GetPlayerController() const;
    FVector GetBarrelWorldLocation() const;

    //Weapon reload

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void LogAmmo();
    
    bool IsAmmoFull();
private:
    FAmmoData CurrentAmmo;
};
