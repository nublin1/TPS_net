// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/BUIUserWidget.h"
#include "GameCoreHUDLayout.generated.h"

class UBUIUserWidget;
/**
 * 
 */
UCLASS()
class TPS_NET_API UGameCoreHUDLayout : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================


	//====================================================================
	// FUNCTIONS
	//====================================================================
	//Getters
	
	UBUIUserWidget* GetTimerWidget() const {return TimerBlock;}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UBUIUserWidget> TimerBlock;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void NativeConstruct() override;
};

