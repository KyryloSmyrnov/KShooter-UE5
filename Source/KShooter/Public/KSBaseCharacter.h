// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KSBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UKSHealthComponent;
class UTextRenderComponent;
class UKSWeaponComponent;

UCLASS()
class KSHOOTER_API AKSBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AKSBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    
    //Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKSHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKSWeaponComponent* WeaponComponent;

    //Animation properties
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    //Damage properties
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //Movement functions
    UFUNCTION(BlueprintCallable, Category="Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category="Movement")
    float GetMovementDirection() const;

private:
    //Movement functions
    bool WantsToRun;
    bool IsMovingForward;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void StartSprint();
    void StopSprint();

    //Health functions
    void OnDeath();
    void OnHealthChanged(float Health);

    //Damage functions
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);

    //Weapon functions
    void SpawnWeapon();
};
