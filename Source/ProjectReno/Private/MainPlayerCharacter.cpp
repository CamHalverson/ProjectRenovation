#include "MainPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

AMainPlayerCharacter::AMainPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set base turn and look up rates
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;
}

void AMainPlayerCharacter::BeginPlay()
{
    Super::BeginPlay()
}

void AMainPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AMainPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &AMainPlayerCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &AMainPlayerCharacter::LookUpAtRate);
}

void AMainPlayerCharacter::MoveForward(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AMainPlayerCharacter::MoveRight(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AMainPlayerCharacter::TurnAtRate(float Rate)
{
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainPlayerCharacter::LookUpAtRate(float Rate)
{
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
