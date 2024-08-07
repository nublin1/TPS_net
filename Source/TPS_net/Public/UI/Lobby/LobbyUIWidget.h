// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "LobbyUIWidget.generated.h"

class UUBUIWButton;
/**
 * 
 */
UCLASS()
class TPS_NET_API ULobbyUIWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================


	//====================================================================
	// FUNCTIONS
	//====================================================================
	ULobbyUIWidget();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta = (BindWidget))
	UUBUIWButton* TogglingReady_Button;

	UPROPERTY(meta = (BindWidget))
	UUBUIWButton* StartMatch_Button;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void NativeConstruct() override;
};
