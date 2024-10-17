#include "MovableMeshActor.h"
#include "Components/InputComponent.h"

AMovableMeshActor::AMovableMeshActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach a static mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Set default movement speed
    MovementSpeed = 100.f;
}

void AMovableMeshActor::BeginPlay()
{
    Super::BeginPlay();
}

void AMovableMeshActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMovableMeshActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &AMovableMeshActor::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &AMovableMeshActor::MoveRight);
    }
}

void AMovableMeshActor::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        FVector Forward = GetActorForwardVector();
        AddActorLocalOffset(Forward * Value * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);
    }
}

void AMovableMeshActor::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        FVector Right = GetActorRightVector();
        AddActorLocalOffset(Right * Value * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);
    }
}
