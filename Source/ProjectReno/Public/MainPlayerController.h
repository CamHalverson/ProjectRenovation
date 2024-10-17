#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

UCLASS()
class YOURGAME_API AMainPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMainPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void OnInteract();  // Example function for interaction
    void OpenInventory(); // Example function for opening inventory
};

