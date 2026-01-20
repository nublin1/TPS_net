// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageType_Knockback.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TPS_NET_API UDamageType_Knockback : public UDamageType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float KnockbackStrength = 700.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bEnableRagdoll = true;
};
