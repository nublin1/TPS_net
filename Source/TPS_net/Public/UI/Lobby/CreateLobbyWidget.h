// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "CreateLobbyWidget.generated.h"

class UUBUIWButton;
class UEditableText;
/**
 * 
 */
UCLASS()
class TPS_NET_API UCreateLobbyWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UEditableText> ServerNameText ;


	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUBUIWButton> WBP_CreateServerButton ;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	//
	UFUNCTION(BlueprintCallable)
	void OnCreateServerButtonClicked();
};
