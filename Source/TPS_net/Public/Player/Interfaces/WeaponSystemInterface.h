// Nublin Studio 2026 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
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
	UFUNCTION(BlueprintCallable)
	virtual class UWeaponSystemComponent* GetWeaponSystemComponent() const = 0;
};
