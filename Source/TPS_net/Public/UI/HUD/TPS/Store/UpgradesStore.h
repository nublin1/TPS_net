// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "UpgradesStore.generated.h"

class UStoreCard;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class TPS_NET_API UUpgradesStore : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UUpgradesStore();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> StoreCardsHolder;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UStoreCard>> StoreCardArray;


	//====================================================================
	// FUNCTIONS
	//====================================================================
	
	virtual void NativeConstruct() override;
};
