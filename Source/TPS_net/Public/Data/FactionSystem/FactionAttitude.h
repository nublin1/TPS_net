// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "FactionAttitude.generated.h"

UENUM(BlueprintType)
enum class EFactionAttitude : uint8
{
	Friendly UMETA(DisplayName="Friendly"),
	Neutral UMETA(DisplayName="Neutral"),
	Hostile UMETA(DisplayName="Hostile")
};

USTRUCT(BlueprintType)
struct FFactionRelation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	FName OtherFaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	EFactionAttitude Attitude = EFactionAttitude::Neutral;
};