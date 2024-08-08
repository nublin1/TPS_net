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

	// Getters
	TObjectPtr<UUBUIWButton> GetTogglingReady_Button() {return TogglingReady_Button;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUBUIWButton* TogglingReady_Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUBUIWButton* StartMatch_Button;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void NativeConstruct() override;
};
