// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStructs.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FCharacterStats CharacterStats;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FName FactionName = "Neutral";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FSenseData SenseData;
};
