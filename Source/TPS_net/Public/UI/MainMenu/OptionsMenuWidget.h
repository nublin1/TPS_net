// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"

#include "OptionsMenuWidget.generated.h"

class UWidgetSwitcher;
class UGraphicsSettings;
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
	
	//
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WS_Settings;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGraphicsSettings> WBP_GraphicsSettings;
	
	//
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Back_Button;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Apply_Button;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION()
	void OnApplyButtonClicked();
};
