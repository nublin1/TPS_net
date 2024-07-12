// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHealthInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UIHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPS_NET_API IIHealthInterface
{
	GENERATED_BODY()

public:
	IIHealthInterface();
	IIHealthInterface(float Health, float MaxHealth);

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================


	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable )
	virtual void TakeDamage(float DamageAmount) = 0;

	virtual float GetHealth() const = 0;
	virtual float GetMaxHealth() const = 0;
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	float Health;
	
	float MaxHealth;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
