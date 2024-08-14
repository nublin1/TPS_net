// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "UI/BUIUserWidget.h"
#include "SettingsOptionSliderRow.generated.h"

class UTextBlock;
class USlider;
/**
 * 
 */
UCLASS()
class TPS_NET_API USettingsOptionSliderRow : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	void InitializeOption(FText OptionName, uint16 InitialValue);

	// Getters
	float GetCurrentValue() const {return CurrentValueSlider->GetValue();}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> OptionNameTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USlider> CurrentValueSlider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentValueTextBlock;

	// TEMPLATE VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionNameText;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativePreConstruct() override;
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void UpdateOptionNameText();

	UFUNCTION()
	virtual void OnSliderValueChanged(float NewValue);
};