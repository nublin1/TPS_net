// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStructs.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxStamina = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MovementSpeed = 600.f;
};

USTRUCT(BlueprintType)
struct FSenseData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	float SenseRadius = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	float VisionAngle = 90.0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	float UpdateInterval = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")
	TArray<TSubclassOf<AActor>> DetectableClasses;
};