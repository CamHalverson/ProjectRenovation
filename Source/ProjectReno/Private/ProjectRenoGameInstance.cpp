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
            SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UProjectRenoGameInstance::OnJoinSessionComplete);
        }
    }
}

void UProjectRenoGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
    if (Succeeded)
    {
        // Start server travel to the specified map
        GetWorld()->ServerTravel("/Game/Scenes/Cam?listen");
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create session: %s"), *SessionName.ToString());
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

void UProjectRenoGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FString JoinAddress;
        if (SessionInterface->GetResolvedConnectString(SessionName, JoinAddress))
        {
            PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get resolved connect string for session: %s"), *SessionName.ToString());
        }
    }
}

void UProjectRenoGameInstance::CreateServer(const FString& SessionName)
{
    UE_LOG(LogTemp, Warning, TEXT("Creating server with session name: %s"), *SessionName);

    FOnlineSessionSettings SessionSettings;
    SessionSettings.bAllowJoinInProgress = true;
    SessionSettings.bIsDedicated = false;
    SessionSettings.bIsLANMatch = true; // Ensure LAN match
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.bUsesPresence = false;
    SessionSettings.NumPublicConnections = 5;

    SessionSettings.Set(FName("SESSION_NAME"), SessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    SessionInterface->CreateSession(0, FName(*SessionName), SessionSettings);
}

void UProjectRenoGameInstance::JoinServer(const FString& SessionName)
{
    DesiredSessionName = SessionName;

    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->bIsLanQuery = true; // Ensure LAN search
    SessionSearch->MaxSearchResults = 100;
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}


