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
	UFUNCTION(BlueprintCallable)
	UButton* GetMainButton() const {return MainButton;}

	UFUNCTION(BlueprintCallable)
	bool GetToggleState() const { return bIsToggleOn; }
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> MainLabel;
	UPROPERTY(EditAnywhere, meta=(EditCondition="MainLabel"))
	FText ButtonText;
	UPROPERTY(EditAnywhere, meta=(EditCondition="MainLabel"))
	float FontSize = 24;
		
	UPROPERTY(EditAnywhere)
	bool bIsToggleButton;
	UPROPERTY(EditAnywhere)
	bool bIsToggleOn;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta=(BindWidget))
	TObjectPtr<UButton> MainButton;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativePreConstruct() override;


	//
	UFUNCTION(BlueprintCallable)
	void HandleButtonClicked();
};
