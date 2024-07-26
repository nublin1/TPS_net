// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UI/BUIUserWidget.h"
#include "UBUIWButton.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class TPS_NET_API UUBUIWButton : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================	
	UUBUIWButton();

	// Getters
	TObjectPtr<UButton> GetMainButton() const {return MainButton;}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> MainLabel;
	UPROPERTY(EditAnywhere, meta=(EditCondition="MainLabel"))
	FText ButtonText;
		
	UPROPERTY(EditAnywhere)
	bool bIsToggleButton;
	UPROPERTY(EditAnywhere)
	bool bIsToggleOn;
		
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UButton> MainButton;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativePreConstruct() override;
	
};
