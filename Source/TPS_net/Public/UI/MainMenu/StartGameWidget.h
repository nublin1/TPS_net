// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "StartGameWidget.generated.h"

class UWidgetSwitcher;
class UUBUIWButton;
/**
 * 
 */
UCLASS()
class TPS_NET_API UStartGameWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	// Getters
	TObjectPtr<UUBUIWButton> GetBack_Button() const {return Back_Button;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WS_StartGame;

	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Single_Button;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Create_Button;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Serverlist_Button;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> Back_Button;


	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	//
	UFUNCTION()
	void OnSingleButtonClicked() const;
	UFUNCTION()
	void OnCreate_ButtonClicked();
	UFUNCTION()
	void OnServerlist_ButtonClicked();
};
