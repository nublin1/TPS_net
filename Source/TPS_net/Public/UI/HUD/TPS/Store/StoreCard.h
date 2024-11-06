// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "Components/StackBox.h"
#include "StoreCard.generated.h"

class UStoreCardRowWidget;
/**
 * 
 */
UCLASS()
class TPS_NET_API UStoreCard : public UBUIUserWidget
{
	GENERATED_BODY()
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UStoreCard();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere)
	FName CardName;
	UPROPERTY(EditAnywhere)
	int CardUnlockPrice = 10000;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UStackBox> Stack_Rows;
	
	UPROPERTY()
	TArray<TObjectPtr<UStoreCardRowWidget>> CardRows;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void NativeConstruct() override;
};
