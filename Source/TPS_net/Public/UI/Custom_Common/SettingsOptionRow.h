// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "SettingsOptionRow.generated.h"

class UUBUIWButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TPS_NET_API USettingsOptionRow : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> OptionNameTextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentValueTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUBUIWButton> DecreaseValueButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUBUIWButton> IncreaseValueButton;

	// defaults
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionNameText;
	// defaults
	UPROPERTY(EditAnywhere)
	FText CurrentValueText;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativePreConstruct() override;
	UFUNCTION()
	virtual void NativeConstruct() override;
};
