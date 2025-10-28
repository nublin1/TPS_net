// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UAIAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPS_NET_API IAIAttackInterface
{
	GENERATED_BODY()

	
public:
    //====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual class UAIAttackComponent* GetAIAttackComponent() const = 0;
};
