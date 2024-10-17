#include "MainPlayerController.h"
#include "MainPlayerCharacter.h"

AMainPlayerController::AMainPlayerController()
{
    // Initialize any necessary parameters here
}

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // You can set input modes or initialize UI elements here if needed
}

void AMainPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Ensure that InputComponent is valid
    if (InputComponent)
    {
        // Bind input actions to functions
        InputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayerController::OnInteract);
        InputComponent->BindAction("OpenInventory", IE_Pressed, this, &AMainPlayerController::OpenInventory);

        // You can bind other actions and axes here
    }
}

void AMainPlayerController::OnInteract()
{
    // Example interaction logic
    ACharacter* ControlledCharacter = GetCharacter();
    if (ControlledCharacter)
    {
        // Perform interaction logic like picking up objects or interacting with doors
    }
}

void AMainPlayerController::OpenInventory()
{
    // Example logic to toggle inventory UI
    // Could involve showing/hiding UI widgets
}
