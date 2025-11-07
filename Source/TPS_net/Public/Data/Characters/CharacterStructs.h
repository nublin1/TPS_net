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

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Melee,
	Ranged,
	AOE,
	Throw,
	SelfDestruct
};

USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	FName AttackName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	EAttackType AttackType = EAttackType::Melee;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float Damage = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float AttackRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float Cooldown = 2.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack")
	FTimerHandle AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	UAnimMontage* AttackMontage = nullptr;
};