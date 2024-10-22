// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectRenoGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UProjectRenoGameInstance::UProjectRenoGameInstance()
{

}

void UProjectRenoGameInstance::Init()
{

	Super::Init();

	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UProjectRenoGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UProjectRenoGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UProjectRenoGameInstance::OnJoinSessionCopmplete);
		}
	}
}

void UProjectRenoGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/Scenes/Cam?listen");
	}
}

void UProjectRenoGameInstance::OnFindSessionComplete(bool Succeeded)
{
	if (Succeeded && SessionSearch.IsValid() && SessionSearch->SearchResults.Num() > 0)
	{
		for (const auto& Result : SessionSearch->SearchResults)
		{
			FString FoundSessionName;

			if (Result.Session.SessionSettings.Settings.Contains(FName("SESSION_NAME")))
			{
				Result.Session.SessionSettings.Settings[FName("SESSION_NAME")].Data.GetValue(FoundSessionName);
				UE_LOG(LogTemp, Warning, TEXT("Found Session: %s"), *FoundSessionName);

				if (FoundSessionName == DesiredSessionName)
				{
					SessionInterface->JoinSession(0, FName(*DesiredSessionName), Result);
					return;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find sessions or no sessions found."));
	}
}

void UProjectRenoGameInstance::OnJoinSessionCopmplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
		{
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UProjectRenoGameInstance::CreateServer(const FString& SessionName)
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer: %s"), *SessionName);

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL") ? false : true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;

	SessionSettings.Set(FName("SESSION_NAME"), SessionName, EOnlineDataAdvertisementType::ViaOnlineService);

	SessionInterface->CreateSession(0, FName(*SessionName), SessionSettings);
}

void UProjectRenoGameInstance::JoinServer(const FString& SessionName)
{
	DesiredSessionName = SessionName;

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL");
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set("SEARCH_PRENENCE", true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

