// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "StoreLayout.generated.h"

class UUpgradesStore;
class UCanvasPanel;
struct FUpgrades;
/**
 * 
 */
UCLASS()
class TPS_NET_API UStoreLayout : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================

	// Getters
	TObjectPtr<UUpgradesStore>& GetUpgradesStore()	{return UpgradesStore;}
	

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCanvasPanel> MainCanvasPanel;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UUpgradesStore> UpgradesStore;

protected:
	//====================================================================
	// FUNCTIONS
	//====================================================================

	virtual void NativeConstruct() override;
};
