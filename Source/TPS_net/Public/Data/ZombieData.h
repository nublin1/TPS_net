// Fill out your copyright notice in the Description page of Project Settings.

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
	
};

USTRUCT()
struct FCharacteristicsOfTheZombie
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, meta=(UIMin = 0.9f, UIMax = 1.1f))
	float WorldScale; 
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
