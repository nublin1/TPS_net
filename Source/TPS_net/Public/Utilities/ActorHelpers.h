#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Components/SceneComponent.h"
#include "ActorHelpers.generated.h"

struct FGameplayAbilitySpec;
struct FGameplayTagContainer;
class UAbilitySystemComponent;

UCLASS()
class TPS_NET_API UActorHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "ActorHelpers")
	static bool HasAnyAbilityWithAssetTags(
		UAbilitySystemComponent* ASC,
		const FGameplayTagContainer& Tags
	);
};

inline bool UActorHelpers::HasAnyAbilityWithAssetTags(UAbilitySystemComponent* ASC, const FGameplayTagContainer& Tags)
{
	if (!ASC)
	{
		return false;
	}

	for (const FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (!Spec.Ability)
		{
			continue;
		}

		if (Spec.Ability->AbilityTags.HasAny(Tags))
		{
			return true;
		}
	}

	return false;
}

