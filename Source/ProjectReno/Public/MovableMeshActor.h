#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovableMeshActor.generated.h"

UCLASS()
class YOURGAME_API AMovableMeshActor : public AActor
{
    GENERATED_BODY()
    
public:    
    AMovableMeshActor();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

private:
    void MoveForward(float Value);
    void MoveRight(float Value);

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float MovementSpeed;
};
