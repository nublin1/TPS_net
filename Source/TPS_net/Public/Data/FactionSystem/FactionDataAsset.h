// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FactionAttitude.h"
#include "Engine/DataAsset.h"
#include "FactionDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TPS_NET_API UFactionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFactionDataAsset();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	FName FactionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	TObjectPtr<UFactionDataAsset> ParentFaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	TArray<TObjectPtr<UFactionDataAsset>> SubFactions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	TArray<FFactionRelation> Relations;

	UFUNCTION(BlueprintCallable, Category="Faction")
	EFactionAttitude GetAttitudeTo(const UFactionDataAsset* Other) const;
};
