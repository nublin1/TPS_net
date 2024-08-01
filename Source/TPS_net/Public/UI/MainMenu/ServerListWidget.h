// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "ServerListWidget.generated.h"

class UUBUIWButton;
class UServerInfoRowWidget;
class UScrollBox;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class TPS_NET_API UServerListWidget : public UBUIUserWidget
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
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> RefleshButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WS_ServerList;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UScrollBox> ServerListScrool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UServerInfoRowWidget> ServerInfoRowWidgetClass;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	//
	UFUNCTION()
	void OnRefleshButtonClicked();

	//
	void OnFindSessionsComplete(bool bWasSuccessful);
	
};
