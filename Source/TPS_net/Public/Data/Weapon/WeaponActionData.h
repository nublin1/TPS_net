// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponActionData.generated.h"

struct FWeaponAbilityData;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TPS_NET_API UWeaponActionData : public UObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 150.0f;
};
