// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UBaseAttackData.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UBaseAttackData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	FName AttackName = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	float Damage = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	float Cooldown = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack")
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;
};

UCLASS(BlueprintType, EditInlineNew)
class UMeleeAttackData : public UBaseAttackData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack|Melee")
	float MeleeAttackRange = 150.f;
};


UCLASS(BlueprintType, EditInlineNew)
class USelfDestuctAttackData : public UBaseAttackData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack|SelfDestuct")
	float InitAttackRange = 150.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack|SelfDestuct")
	float ExplosionRad = 550.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attack|SelfDestuct")
	float TimeToDetonate = 2.5f;
};