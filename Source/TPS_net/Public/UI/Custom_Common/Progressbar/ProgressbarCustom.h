// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "ProgressbarCustom.generated.h"

class UTextBlock;
class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class TPS_NET_API UProgressbarCustom : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UProgressbarCustom();

	// 
	UFUNCTION(BlueprintCallable)
	void SetProgress(float Progress) const;
	UFUNCTION(BlueprintCallable)
	void SetFillColor(FLinearColor NewColor);
	UFUNCTION(BlueprintCallable)
	void SetMaxValue(float NewValue);
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue(float NewValue);
	UFUNCTION(BlueprintCallable)
	void UpdateText();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Widgets
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* Icon;
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TextNumbers;

	//
	UPROPERTY()
	int MaxValue = 100;
	UPROPERTY()
	float CurrentValue = 10;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void NativeConstruct() override;
};
