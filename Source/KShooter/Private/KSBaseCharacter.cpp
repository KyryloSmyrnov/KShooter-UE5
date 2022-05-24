// KShooter - All Rights Reserved

#include "KSBaseCharacter.h"
#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/KSWeaponComponent.h"
#include "Components/KSCharacterMovementComponent.h"
#include "Components/KSHealthComponent.h"
#include "Components/TextRenderComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);


AKSBaseCharacter::AKSBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UKSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    //Spring Arm Component
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    //Camera components
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    //Health components
    HealthComponent = CreateDefaultSubobject<UKSHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    //Weapon components
    WeaponComponent = CreateDefaultSubobject<UKSWeaponComponent>("WeaponComponent");
}


void AKSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &AKSBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AKSBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AKSBaseCharacter::OnGroundLanded);
}


void AKSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void AKSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);

    //Axis binds
    PlayerInputComponent->BindAxis("MoveForward", this, &AKSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKSBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AKSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AKSBaseCharacter::AddControllerYawInput);
    //Actions binds
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AKSBaseCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AKSBaseCharacter::StopSprint);
    PlayerInputComponent->BindAction("Shoot", IE_Pressed, WeaponComponent, &UKSWeaponComponent::StartShoot);
    PlayerInputComponent->BindAction("Shoot", IE_Released, WeaponComponent, &UKSWeaponComponent::StopShoot);
    PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &UKSWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Released, WeaponComponent, &UKSWeaponComponent::Reload);

}


//Movement functions
void AKSBaseCharacter::MoveForward(float Amount)
{
    if (Amount == 0)
        return;
    IsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AKSBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AKSBaseCharacter::StartSprint()
{
    WantsToRun = true;
}

void AKSBaseCharacter::StopSprint()
{
    WantsToRun = false;
}

bool AKSBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AKSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

//Health functions
void AKSBaseCharacter::OnDeath()
{
    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);

    if (Controller)
        Controller->ChangeState(NAME_Spectating);
    
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopShoot();
}

void AKSBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

//Damage functions
void AKSBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;

    if (FallVelocityZ < LandedDamageVelocity.X)
        return;
    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}
