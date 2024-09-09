// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ZombieCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UZombieCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPS_NET_API IZombieCombatInterface
{
	GENERATED_BODY()

	
public:
    //====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual class UZombieCombatComponent* GetZombieCombatComponent() const = 0;
};
