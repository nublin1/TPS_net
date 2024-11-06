// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "StoreCardRowWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class TPS_NET_API UStoreCardRowWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UStoreCardRowWidget();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UpgradeType;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentValue;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UpgradeValue;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
};
