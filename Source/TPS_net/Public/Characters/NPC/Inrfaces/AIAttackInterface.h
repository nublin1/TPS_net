// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetCurrentTarget() const;
};
