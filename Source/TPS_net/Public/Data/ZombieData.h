// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ZombieData.generated.h"

/**
 * 
 */
USTRUCT()
struct FZombieAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UAnimMontage* BasicAttackAnimMontage;
};

USTRUCT()
struct FCharacteristicsOfTheZombie
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float MinWorldScale = 0.9f;
	UPROPERTY(EditAnywhere)
	float MaxWorldScale = 1.1f;

	UPROPERTY(EditAnywhere)
	float RunSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	int MaxHealth = 100;
};

USTRUCT()
struct TPS_NET_API FZombieData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	FZombieAssetData ZombieAssetData;

	UPROPERTY(EditAnywhere)
	FCharacteristicsOfTheZombie CharacteristicsOfTheZombie;
};
