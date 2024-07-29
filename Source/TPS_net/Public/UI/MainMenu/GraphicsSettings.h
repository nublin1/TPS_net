// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "GraphicsSettings.generated.h"

class USettingsOptionRow;
/**
 * 
 */
UCLASS()
class TPS_NET_API UGraphicsSettings : public UBUIUserWidget
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
	TObjectPtr<USettingsOptionRow> GetOption_WindowMode() const
	{
		return Option_WindowMode;
	}

	TObjectPtr<USettingsOptionRow> GetOption_Resolution() const
	{
		return Option_Resolution;
	}

	TObjectPtr<USettingsOptionRow> GetOption_VSync() const
	{
		return Option_VSync;
	}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USettingsOptionRow> Option_WindowMode;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USettingsOptionRow> Option_Resolution;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USettingsOptionRow> Option_VSync;

	//
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EWindowMode::Type> ChoosenWindowMode = EWindowMode::Fullscreen;


	FTimerHandle tim;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;
};
