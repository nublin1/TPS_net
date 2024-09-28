// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "TimerWidget.generated.h"

class UTextBlock;
/**
 * 
 */



UCLASS()
class TPS_NET_API UTimerWidget : public UBUIUserWidget
{
	GENERATED_BODY()
	
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	void SighUp();
	
	UFUNCTION(BlueprintCallable)
	void UpdateTimerName(FText NewText);
	UFUNCTION(BlueprintCallable)
	void UpdateTimerText(int RemainingTime);

	UFUNCTION(BlueprintCallable)
	void SetTimerColor(FSlateColor NewColor);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadOnly, meta =(BindWidgetOptional))
	TObjectPtr<UTextBlock> TimerName;
	UPROPERTY(BlueprintReadOnly, meta =(BindWidget))
	TObjectPtr<UTextBlock> TimerBlock;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
};
