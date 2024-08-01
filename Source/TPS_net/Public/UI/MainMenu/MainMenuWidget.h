// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "MainMenuWidget.generated.h"

class UStartGameWidget;
class UWidgetSwitcher;
class UOptionsMenuWidget;
class UUBUIWButton;
/**
 * 
 */
UCLASS()
class TPS_NET_API UMainMenuWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UOptionsMenuWidget> OptionsMenuWidget;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> SW_MainMenu;
	UPROPERTY(EditAnywhere, meta=(OptionalWidget))
	TObjectPtr<UStartGameWidget> WBP_StartGame;
	
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Start_Button;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Settings_Button;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Quit_Button;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	
	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnInStartGameBackButtonClicked();
};
