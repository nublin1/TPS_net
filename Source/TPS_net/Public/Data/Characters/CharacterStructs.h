// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "CharacterStructs.generated.h"

class UGameplayAbility;

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

UENUM(BlueprintType)
enum class EFallImpactType : uint8
{
	None        UMETA(DisplayName = "None"),
	//Light       UMETA(DisplayName = "Light"),
	//Medium      UMETA(DisplayName = "Medium"),
	Heavy       UMETA(DisplayName = "Heavy"),
	Ragdoll		UMETA(DisplayName = "Ragdoll")
};


/** Ability Ended Data */
USTRUCT(BlueprintType, Blueprintable)
struct FAbilityEndedDataBlueprintWrapper
{
	GENERATED_USTRUCT_BODY()

	FAbilityEndedDataBlueprintWrapper()
		: AbilityThatEnded(nullptr)
		, bReplicateEndAbility(false)
		, bWasCancelled(false)
	{
	}

	FAbilityEndedDataBlueprintWrapper(UGameplayAbility* InAbility, FGameplayAbilitySpecHandle InHandle, bool bInReplicateEndAbility, bool bInWasCancelled)
		: AbilityThatEnded(InAbility)
		, AbilitySpecHandle(InHandle)
		, bReplicateEndAbility(bInReplicateEndAbility)
		, bWasCancelled(bInWasCancelled)
	{
	}

	/** Ability that ended, normally instance but could be CDO */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGameplayAbility> AbilityThatEnded;
	UPROPERTY(blueprintReadOnly)
	FGameplayTagContainer GameplayTagContainer;

	/** Specific ability spec that ended */
	UPROPERTY(BlueprintReadOnly)
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	/** Rather to replicate the ability to ending */
	UPROPERTY(BlueprintReadOnly)
	bool bReplicateEndAbility;

	/** True if this was cancelled deliberately, false if it ended normally */
	UPROPERTY(BlueprintReadOnly)
	bool bWasCancelled;
};