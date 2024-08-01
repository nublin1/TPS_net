// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UI/BUIUserWidget.h"

#include "ServerInfoRowWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class TPS_NET_API UServerInfoRowWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual void UpdateText();
	
	// Setters
	
	virtual void SetOnlineSession(const FOnlineSessionSearchResult& NewOnlineSession) {OnlineSession = NewOnlineSession; };

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	FOnlineSessionSearchResult OnlineSession;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PlayerName ;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NumPlayers ;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Ping ;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;
};
