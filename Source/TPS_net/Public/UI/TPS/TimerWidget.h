// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "TimerWidget.generated.h"

class UTextBlock;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerExpired); 

UCLASS()
class TPS_NET_API UTimerWidget : public UBUIUserWidget
{
	GENERATED_BODY()
	
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	FOnTimerExpired OnTimerExpired;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	void SighUp();
	
	UFUNCTION(BlueprintCallable)
	void UpdateTimerName(FText NewText);
	UFUNCTION(BlueprintCallable)
	void UpdateTimerText(int32 Minutes, int32 Seconds);

	UFUNCTION(BlueprintCallable)
	void SetTimerColor(FSlateColor NewColor);

	UFUNCTION(BlueprintCallable)
	void SetTimerDelay(int NewTime) {TimerDelay = NewTime;}
	UFUNCTION(BlueprintCallable)
	void StartTimer();
	UFUNCTION(BlueprintCallable)
	void StopTimer();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadOnly, meta =(BindWidgetOptional))
	TObjectPtr<UTextBlock> TimerName;
	UPROPERTY(BlueprintReadOnly, meta =(BindWidget))
	TObjectPtr<UTextBlock> TimerBlock;

	UPROPERTY()
	FTimerHandle TimerHandle;
	UPROPERTY()
	int TimerDelay = 60;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	
};
