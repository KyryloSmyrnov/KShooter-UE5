// KShooter - All Rights Reserved


#include "Components/KSWeaponComponent.h"
#include "Weapon/KSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animation/KSEquipFinishedAnimNotify.h"
#include "Animation/KSReloadFinishedAnimNotify.h"
#include "Animation/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UKSWeaponComponent::UKSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UKSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
    InitAnimation();
}

void UKSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UKSWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());

    if (!GetWorld() || !Character)
        return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<AKSBaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon)
            continue;

        Weapon->OnClipEmpty.AddUObject(this, &UKSWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UKSWeaponComponent::AttachWeaponToSocket(AKSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent)
        return;
    FAttachmentTransformRules AttachmentRools(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRools, SocketName);
}

void UKSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
        return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopShoot();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
    {
        return Data.WeaponClass == CurrentWeapon->GetClass();
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UKSWeaponComponent::StartShoot()
{
    if (!CanFire())
        return;
    CurrentWeapon->StartShoot();
}

void UKSWeaponComponent::StopShoot()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopShoot();
}

void UKSWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UKSWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    Character->PlayAnimMontage(Animation);
}

void UKSWeaponComponent::InitAnimation()
{
    if (!EquipAnimMontage)
        return;

    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UKSEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UKSWeaponComponent::OnEquipFinished);
    } else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgetten to set"));
        checkNoEntry();
    }

    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UKSReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);

        ReloadFinishedNotify->OnNotified.AddUObject(this, &UKSWeaponComponent::OnReloadFinished);
    }
}

void UKSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh())
        return;

    EquipAnimInProgress = false;
}

void UKSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh())
        return;

    ReloadAnimInProgress = false;
}

bool UKSWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UKSWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UKSWeaponComponent::CanReload() const
{
    return CurrentWeapon                  //
           && !EquipAnimInProgress        //
           && !ReloadAnimInProgress       //
           && CurrentWeapon->CanReload(); //
}

void UKSWeaponComponent::Reload()
{
    ChangeClip();
}

void UKSWeaponComponent::OnEmptyClip(AKSBaseWeapon* AmmoEmptyWeapon)
{
    if(!AmmoEmptyWeapon) return;
    
    if(CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for(const auto Weapon: Weapons)
        {
            if(Weapon == AmmoEmptyWeapon)
            {
                Weapon->ChangeClip();
            }
        }
    }
}

void UKSWeaponComponent::ChangeClip()
{
    if (!CanReload())
        return;

    CurrentWeapon->StopShoot();
    CurrentWeapon->ChangeClip();
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

bool UKSWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    if(CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool UKSWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    if(CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}
    
bool UKSWeaponComponent::TryToAddAmmo(TSubclassOf<AKSBaseWeapon> WeaponType, int32 ClipsAmount)
{
    for(const auto Weapon: Weapons)
    {
        if(Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
}
