// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "UI/BUIUserWidget.h"
#include "Utilities/GeneralUtils.h"
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
	void InitializeOption(FText OptionName, uint16 InitialValue, TArray<FText> PossibleValues);

	// Getters
	UFUNCTION()
	TArray<FText> GetPossibleValuesText() const {return PossibleValuesText;}
	UFUNCTION()
	int32 GetCurrentIndex() const {return CurrentIndex;}


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
	
	
	// TEMPLATE VARIABLES
	UPROPERTY()
	TArray<FText> PossibleValuesText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionNameText;
	UPROPERTY()
	int32 CurrentIndex = 0;
	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativePreConstruct() override;
	UFUNCTION()
	virtual void NativeConstruct() override;

	//
	UFUNCTION()
	void OnDecreaseButtonClicked();
	UFUNCTION()
	void OnIncreaseButtonClicked();
	UFUNCTION()
	void UpdateOptionNameText() const;
	UFUNCTION()
	void UpdateCurrentValueText();
	

	UFUNCTION()
	void ChangeValue(bool bIncrease);
};
