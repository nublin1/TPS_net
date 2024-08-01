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
}

void UMultiplayerGameInstance::CreateServer(FName ServerName, int32 MaxPlayers)
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
			OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UMultiplayerGameInstance::OnDestroySessionComplete);
			OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);

			SessionInterface->DestroySession(ServerName);
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
		// "SessionSearch->SearchResults" is an Array that contains all the information. You can access the Session in this and get a lot of information
		for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session Number: %d | Sessionname: %s "), SearchIdx+1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName)));
		}
	}
}
