// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "WeaponData.generated.h"

/**
 * 
 */

class ABaseBulletActor;

UENUM(Blueprintable, BlueprintType)
enum class EWeaponType : uint8
{
	Primary UMETA(DisplayName = "Primary"),
	Pistol	UMETA(DisplayName = "Pistol"),
};

UENUM(meta=(ScriptName="EHolsterWeaponType"))
enum class EHolsterWeaponType : uint8
{
	None				UMETA(DisplayName = "None"),
	Primary				UMETA(DisplayName = "Primary"),
	AlternativePrimary	UMETA(DisplayName = "AlternativePrimary"),
	Pistol				UMETA(DisplayName = "Pistol"),
};

UENUM(Blueprintable, BlueprintType)
enum class EBulletMode
{
	HitScan		UMETA(DisplayName = "HitScan"),
	Projectile	UMETA(DisplayName = "Projectile"),
};

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	Single        UMETA(DisplayName = "Single"),
	Burst         UMETA(DisplayName = "Burst"),
	Full_Auto     UMETA(DisplayName = "Full_Auto"),
};

USTRUCT()
struct FWeaponAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, meta=(EditCondition="BulletMode == EBulletMode::Projectile"))
	UBlueprint* BulletActor;

	UPROPERTY(EditAnywhere)
	UAnimBlueprint* AnimationBlueprint;

	UPROPERTY(EditAnywhere)
	FName BulletSpawnSocketTransformName = "MuzzleFlash";
};

USTRUCT()
struct FCharacteristicsOfTheWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Weapon Characteristics")
	TArray<EFireMode> AvailableShootingModes;
	UPROPERTY(EditAnywhere,Category = "Weapon Characteristics")
	float WeaponMass = 1.0f; // kilograms
	UPROPERTY(EditAnywhere,Category = "Weapon Characteristics")
	float SpreadAngle = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Weapon Characteristics")
	float RPM = 600; //Rounds per minute	
	UPROPERTY(EditAnywhere, Category = "Weapon Characteristics")
	uint16 MagazineSize = 30; // Rounds
	UPROPERTY(EditAnywhere, Category = "Weapon Characteristics")
	float BulletMass = 0.100f; // kilograms
	UPROPERTY(EditAnywhere, Category = "Weapon Characteristics")
	float MuzzleVelocity = 55000; // cm/sec

	FCharacteristicsOfTheWeapon()
	{
		AvailableShootingModes = {EFireMode::Single};
	}
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
	EBulletMode BulletMode;

	UPROPERTY(EditAnywhere)
	FCharacteristicsOfTheWeapon CharacteristicsOfTheWeapon;

	UPROPERTY(EditAnywhere)
	FWeaponAssetData WeaponAssetData;	
	
};

UCLASS(Blueprintable)
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

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	static int CastEnumToInt(EWeaponType EnumValue)
	{
		return static_cast<int>(EnumValue);
	}
};
