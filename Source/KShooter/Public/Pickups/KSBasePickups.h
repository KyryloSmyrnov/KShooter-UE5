// KShooter - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KSBasePickups.generated.h"

class USphereComponent;

UCLASS()
class KSHOOTER_API AKSBasePickups : public AActor
{
    GENERATED_BODY()

public:
    AKSBasePickups();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;
    
private:
    float RotationYaw = 0.0f;
    virtual bool GivePickupTo(APawn* PlayerPawn);
    
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
