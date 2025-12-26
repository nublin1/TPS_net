// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UAbilityBase();

	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Ability")
	bool ShouldShowInAbilitiesBar = false;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
};
