// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/MultiplayerGameInstance.h"

#include "AdvancedSteamFriendsLibrary.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineUserInterface.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerGameInstance::UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnStartOnlineGameComplete);

	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnFindSessionsComplete);
	
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
			StartCreateSession(bIsLAN);
		}
		else
		{
			StartCreateSession(bIsLAN);
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
	SessionSearch->bIsLanQuery = bIsLAN;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "STEAM")	{SessionSearch->bIsLanQuery = false;}
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
	if (localPlayer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UserId %s"), *localPlayer->GetPreferredUniqueNetId()->ToString()));
		SessionInterface->FindSessions(0, SearchSettingsRef);
	}
	else
	{
		OnFindSessionsComplete(false);
	}

	
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
			//World->ServerTravel("/Game/ThirdPerson/Maps/Lobby?listen");
			
		}
		const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		RegisterPlayer(SessionName, localPlayer->GetPreferredUniqueNetId(), false);
		UGameplayStatics::OpenLevel(GetWorld(), "Lobby", true, "listen");
	}
}

void UMultiplayerGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
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
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int32>(Result)));
			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			RegisterPlayer(SessionName, localPlayer->GetPreferredUniqueNetId(), false);
			PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
			
		}
	}
}

void UMultiplayerGameInstance::StartCreateSession(bool bIsLAN)
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if (Session.IsValid())
		{			
			TSharedPtr<class FOnlineSessionSettings> newSessionSettings = MakeShareable(new FOnlineSessionSettings());
			newSessionSettings-> bIsLANMatch = bIsLAN;
			if (IOnlineSubsystem::Get()->GetSubsystemName() == "STEAM")	{newSessionSettings->bIsLANMatch = false;}
			newSessionSettings-> bUsesPresence = true;
			newSessionSettings-> NumPublicConnections = PendingMaxPlayers;
			newSessionSettings-> bShouldAdvertise = true;
			newSessionSettings-> NumPrivateConnections = 0;
			newSessionSettings-> bAllowInvites = true;
			newSessionSettings-> bAllowJoinInProgress = true;
			newSessionSettings-> bAllowJoinViaPresence = true;
			newSessionSettings-> bAllowJoinViaPresenceFriendsOnly = false;
			newSessionSettings->bUseLobbiesIfAvailable = true;

			newSessionSettings->Set(SETTING_MAPNAME, FString("Lobby"), EOnlineDataAdvertisementType::ViaOnlineService);
		
			OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UserId %s"), *localPlayer->GetPreferredUniqueNetId()->ToString()));
			SessionInterface->CreateSession(0,  PendingServerName, *newSessionSettings);
			
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

void UMultiplayerGameInstance::RegisterPlayer(FName SessionName, const FUniqueNetIdRepl& PlayerID, bool bWasInvited)
{
	SessionInterface->RegisterPlayer(SessionName, *PlayerID, false);
}

void UMultiplayerGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OFindSessionsComplete bSuccess: %d"), bWasSuccessful));

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
			FindSessionsCompleteDelegate.Broadcast(bWasSuccessful, Results);
		}
	}
	else
	{
		if (FindSessionsCompleteDelegate.IsBound())
		{
			const TArray<FCustomSessionSearchResult> Results;
			FindSessionsCompleteDelegate.Broadcast(bWasSuccessful, Results);
		}
		
	}
}


