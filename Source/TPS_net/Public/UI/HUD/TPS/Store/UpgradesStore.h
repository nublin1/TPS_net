// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "UpgradesStore.generated.h"

struct FUpgrades;
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

	UFUNCTION(BlueprintCallable)
	void InitUpgradesStore(FUpgrades UpgradesList);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> StoreCardsHolder;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int StoreCardsHolderRowsNumber;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int StoreCardsHolderCollumsNumber;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UStoreCard>> StoreCardArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UStoreCard> StoreCardClass;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	
	virtual void NativeConstruct() override;
};
