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

struct FBlueprintSessionResult;

USTRUCT(BlueprintType)
struct FCustomSessionSearchResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	FString HostUserName;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 MaxPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 CurrentPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 Ping;
	
	FOnlineSessionSearchResult SearchResult;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFindSessionsCompleteDelegate, bool, bWasSuccessful, TArray<FCustomSessionSearchResult>, SessionSearchResult);

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


	FFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category = "Network")
	void CreateServer(FName ServerName, int32 MaxPlayers, bool bIsLAN);
	UFUNCTION(BlueprintCallable, Category = "Network")
	void FindSessions(bool bIsLAN, bool bIsPresence);
	
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

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

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void Shutdown() override;
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);	
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void StartCreateSession(bool bIsLAN);
	void DestroyCurrentSession();
	void RegisterPlayer(FName SessionName, const FUniqueNetIdRepl& PlayerID, bool bWasInvited = false);
	
	void OnFindSessionsComplete(bool bWasSuccessful);

	

private:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	FName PendingServerName;
	int32 PendingMaxPlayers;
};
