// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlinePlayerCharacter.h"

// Sets default values
AOnlinePlayerCharacter::AOnlinePlayerCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOnlinePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOnlinePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

