// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Upgrades/UpgradeData.h"
#include "UObject/NoExportTypes.h"
#include "UpgradeBase.generated.h"

struct FBaseUpgrade;
/**
 * 
 */
UCLASS()
class TPS_NET_API UUpgradeBase : public UObject
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UUpgradeBase();

	// Getters
	UFUNCTION(BlueprintCallable)
	TArray<FBaseUpgrade> GetUpgrade() {return UpgradesList;}
	

	// Setters
	UFUNCTION(BlueprintCallable)
	void SetUpgrades(TArray<FBaseUpgrade> NewUpgradesList) {this->UpgradesList = NewUpgradesList;}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBaseUpgrade> UpgradesList;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	
};
