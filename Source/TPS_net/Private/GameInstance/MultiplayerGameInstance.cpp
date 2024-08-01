// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/MultiplayerGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerGameInstance::UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnStartOnlineGameComplete);
	
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnDestroySessionComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnJoinSessionComplete);
}

void UMultiplayerGameInstance::CreateServer(FName ServerName, int32 MaxPlayers, bool bIsLAN)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("GetSubsystemName %s"), *OnlineSubsystem->GetSubsystemName().ToString()));
	SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (SessionInterface.IsValid())
	{
		PendingServerName = ServerName;
		PendingMaxPlayers = MaxPlayers;
		
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(ServerName);
		if (ExistingSession != nullptr && ExistingSession->OwningUserId == OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(0))
		{
			DestroyCurrentSession();
		}
		else
		{
			StartCreateSession();
		}
	}
	
}

void UMultiplayerGameInstance::FindSessions(bool bIsLAN, bool bIsPresence)
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		OnFindSessionsComplete(false);
	}
	SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		OnFindSessionsComplete(false);
	}
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	SessionSearch->MaxSearchResults = 50;
	SessionSearch->PingBucketSize = 100;
	
	// Set this Query Setting if "bIsPresence" is true
	if (bIsPresence)
	{
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
	}
	TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();
	// Set the Delegate to the Delegate Handle of the FindSession function
	OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			
	// Call the SessionInterface function. The Delegate gets called once this is finished
	const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UserId %s"), *localPlayer->GetPreferredUniqueNetId()->ToString()));
	SessionInterface->FindSessions(*localPlayer->GetPreferredUniqueNetId(), SearchSettingsRef);

	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnFindSessionsComplete);
}

bool UMultiplayerGameInstance::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName,
	const FOnlineSessionSearchResult& SearchResult)
{
	bool bSuccessful = false;
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		return bSuccessful;
	}

	if (SessionInterface.IsValid())
	{
		OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
		bSuccessful = SessionInterface->JoinSession(*UserId, SessionName, SearchResult);
	}
	
	return bSuccessful;
}

void UMultiplayerGameInstance::Shutdown()
{
	Super::Shutdown();

	DestroyCurrentSession();
}

void UMultiplayerGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));
	
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);	
		if (bWasSuccessful)
		{
			OnStartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
			SessionInterface->StartSession(SessionName);
		}
	}
}

void UMultiplayerGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
	}

	if (bWasSuccessful)
	{
		StartCreateSession();
	}
}

void UMultiplayerGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

	if (SessionInterface)
	{
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
	
	}

	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Maps/Lobby?listen");
			
		}
		//UGameplayStatics::OpenLevel(GetWorld(), "NewMap", true, "listen");
	}
}

void UMultiplayerGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int32>(Result)));

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		return;
	}

	if (SessionInterface.IsValid())
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
		APlayerController * const PlayerController = GetFirstLocalPlayerController();

		FString TravelURL;
		if (PlayerController && SessionInterface->GetResolvedConnectString(SessionName, TravelURL))
		{
			PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UMultiplayerGameInstance::StartCreateSession()
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid())
		{
			TSharedPtr<class FOnlineSessionSettings> newSessionSettings = MakeShareable(new FOnlineSessionSettings());
			newSessionSettings-> bIsLANMatch = true;
			newSessionSettings-> bUsesPresence = true;
			newSessionSettings-> NumPublicConnections = PendingMaxPlayers;
			newSessionSettings-> bShouldAdvertise = true;
			newSessionSettings-> NumPrivateConnections = 0;
			newSessionSettings-> bAllowInvites = true;
			newSessionSettings-> bAllowJoinInProgress = true;
			newSessionSettings-> bAllowJoinViaPresence = true;
			newSessionSettings-> bAllowJoinViaPresenceFriendsOnly = false;
			newSessionSettings->bUseLobbiesIfAvailable = true;
		
			OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UserId %s"), *localPlayer->GetPreferredUniqueNetId()->ToString()));
			SessionInterface->CreateSession(*localPlayer->GetPreferredUniqueNetId(),  PendingServerName, *newSessionSettings);
			
		}
	}
	else
	{
		if(GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsytem found!"));
	}
}

void UMultiplayerGameInstance::DestroyCurrentSession()
{
	if (SessionInterface.IsValid())
	{
		
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(PendingServerName);
		if (ExistingSession != nullptr)
		{
			OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
			SessionInterface->DestroySession(PendingServerName);
		}
	}
}

void UMultiplayerGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OFindSessionsComplete bSuccess: %d"), bWasSuccessful));

	// Get OnlineSubsystem we want to work with
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (!OnlineSubsystem)
	{
		return;
	}

	SessionInterface = OnlineSubsystem->GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		return;
	}

	// Clear the Delegate handle, since we finished this call
	SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

	// Just debugging the Number of Search results. Can be displayed in UMG or something later on
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));

	
	
	if (SessionSearch->SearchResults.Num() > 0)
	{
		TArray<FCustomSessionSearchResult> Results;
		for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
		{
			FCustomSessionSearchResult CustomResult;
			CustomResult.HostUserName = SessionSearch->SearchResults[SearchIdx].Session.OwningUserName;
			CustomResult.MaxPlayers = SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.NumPublicConnections;
			CustomResult.CurrentPlayers = CustomResult.MaxPlayers - SessionSearch->SearchResults[SearchIdx].Session.NumOpenPublicConnections;
			CustomResult.Ping = SessionSearch->SearchResults[SearchIdx].PingInMs;
			CustomResult.SearchResult = SessionSearch->SearchResults[SearchIdx];
			Results.Add(CustomResult);

			// Add more debug information
			FString DebugMessage = FString::Printf(TEXT("Host: %s, MaxPlayers: %d, OpenConnections: %d, CurrentPlayers: %d, Ping: %d"),
				*CustomResult.HostUserName, CustomResult.MaxPlayers,
				SessionSearch->SearchResults[SearchIdx].Session.NumOpenPublicConnections,
				CustomResult.CurrentPlayers, CustomResult.Ping);

			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, DebugMessage);

		}
		
		if (FindSessionsCompleteDelegate.IsBound())
		{
			FindSessionsCompleteDelegate.Broadcast(Results);
		}
	}
}
