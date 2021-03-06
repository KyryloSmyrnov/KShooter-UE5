// KShooter - All Rights Reserved


#include "Pickups/KSBasePickups.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

AKSBasePickups::AKSBasePickups()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void AKSBasePickups::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);
    GenerateRotationYaw();
}

void AKSBasePickups::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void AKSBasePickups::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if(GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

bool AKSBasePickups::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void AKSBasePickups::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if(GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }
    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AKSBasePickups::Respawn, RespawnTime);
}

void AKSBasePickups::Respawn()
{
    GenerateRotationYaw();
    
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if(GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void AKSBasePickups::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
