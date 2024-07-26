// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "OptionsMenuWidget.generated.h"

class UUBUIWButton;
/**
 * 
 */
UCLASS()
class TPS_NET_API UOptionsMenuWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================

	// Setters
	void SetPrevActiveWidget(TObjectPtr<UBUIUserWidget> PrevWidget) {PrevActiveWidget = PrevWidget;}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	TObjectPtr<UBUIUserWidget> PrevActiveWidget;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Back_Button;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	
	UFUNCTION()
	void OnBackButtonClicked();
};
