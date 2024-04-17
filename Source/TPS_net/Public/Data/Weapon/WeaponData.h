// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponData.generated.h"

/**
 * 
 */

UENUM()
enum class EHolsterType : uint8
{
	Primary UMETA(DisplayName = "Primary"),
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
	EHolsterType HolsterType;

	UPROPERTY(EditAnywhere)
	FWeaponAssetData WeaponAssetData;	
	
};

UCLASS()
class TPS_NET_API UWeaponHelper : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	static FName ConvertHolsterTypeToText(const EHolsterType HolsterType)
	{
		switch (HolsterType)
		{
		case EHolsterType::Primary:
			return FName("Primary");
		case EHolsterType::Pistol:
			return FName("R_PistolHolster");
		default:
			return FName("");
		}
	}
};
