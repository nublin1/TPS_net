// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class TPS_NET_API UMultiplayerGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category = "Network")
	void CreateServer(FName ServerName, int32 MaxPlayers);
	UFUNCTION(BlueprintCallable, Category = "Network")
	void FindSessions(bool bIsLAN, bool bIsPresence);

	// Getters
	TSharedPtr<class FOnlineSessionSearch> GetSessionSearch() {return SessionSearch;}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	IOnlineSessionPtr SessionInterface;	
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	void StartCreateSession();

	void OnFindSessionsComplete(bool bWasSuccessful);

private:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	FName PendingServerName;
	int32 PendingMaxPlayers;
};
