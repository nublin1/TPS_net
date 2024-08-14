// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "AudioSettingsWidget.generated.h"

class USettingsOptionSliderRow;
/**
 * 
 */
UCLASS()
class TPS_NET_API UAudioSettingsWidget : public UBUIUserWidget
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
	TObjectPtr<USettingsOptionSliderRow> GetOptionMasterVolum() const {return OptionMasterValue;};

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USettingsOptionSliderRow> OptionMasterValue;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;
};
