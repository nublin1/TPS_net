// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPS_NET_API IWeaponSystemInterface
{
	GENERATED_BODY()

	
public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual class UWeaponSystemComponent* GetWeaponSystemComponent() const = 0;
};
