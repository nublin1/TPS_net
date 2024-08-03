// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "GameInstance/MultiplayerGameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UI/BUIUserWidget.h"
#include "GameInstance/MultiplayerGameInstance.h"

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
	UFUNCTION(BlueprintCallable)
	virtual void SetOnlineSession(FCustomSessionSearchResult NewOnlineSession) {Session = NewOnlineSession; }

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	FCustomSessionSearchResult Session;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* PlayerName ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> NumPlayers ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Ping ;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
