// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Engine/GameInstance.h"
#include "ProjectRenoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRENO_API UProjectRenoGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UProjectRenoGameInstance();

protected:
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;

	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName SessionName, bool Succeeded);
	virtual void OnFindSessionComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
	void CreateServer(const FString& SessionName);

	UFUNCTION(BlueprintCallable)
	void JoinServer(const FString& SessionName);

	FString DesiredSessionName;
	
};
