// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponData.generated.h"

/**
 * 
 */

UENUM(Blueprintable, BlueprintType)
enum class EWeaponType : uint8
{
	Primary UMETA(DisplayName = "Primary"),
	Pistol UMETA(DisplayName = "Pistol"),
};

UENUM(meta=(ScriptName="EHolsterWeaponType"))
enum class EHolsterWeaponType : uint8
{
	None UMETA(DisplayName = "None"),
	Primary UMETA(DisplayName = "Primary"),
	AlternativePrimary UMETA(DisplayName = "AlternativePrimary"),
	Pistol UMETA(DisplayName = "Pistol"),
};

USTRUCT()
struct FWeaponAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;
};

USTRUCT()
struct TPS_NET_API FWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	EWeaponType HolsterType = EWeaponType::Primary;

	UPROPERTY(EditAnywhere)
	FWeaponAssetData WeaponAssetData;	
	
};

UCLASS()
class TPS_NET_API UWeaponHelper : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	static FName ConvertHolsterTypeToText(const EWeaponType HolsterType)
	{
		switch (HolsterType)
		{
		case EWeaponType::Primary:
			return FName("PrimaryHolster");
		case EWeaponType::Pistol:
			return FName("R_PistolHolster");
		default:
			return FName("");
		}
	}

	
};
