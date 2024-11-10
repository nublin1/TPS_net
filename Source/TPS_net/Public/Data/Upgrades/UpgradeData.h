#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "UpgradeData.generated.h"

enum class EFireMode : uint8;

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	Damage       UMETA(DisplayName = "Damage"),
	MagazineSize UMETA(DisplayName = "Magazine Size"),
	FireMode     UMETA(DisplayName = "Fire Mode"),
	AmmoType     UMETA(DisplayName = "Ammo Type")
};


USTRUCT(Blueprintable)
struct FBaseUpgrade 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUpgradeType UpgradeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfUpgrades = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> UpgradeCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="UpgradeType == EUpgradeType::Damage", EditConditionHides))
	float DamageValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="UpgradeType == EUpgradeType::MagazineSize", EditConditionHides))
	int32 MagazineSizeValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="UpgradeType == EUpgradeType::FireMode", EditConditionHides))
	EFireMode FireModeValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="UpgradeType == EUpgradeType::AmmoType", EditConditionHides))
	FName AmmoTypeValue;
};

USTRUCT(BlueprintType)
struct FWeaponUpgradeRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBaseUpgrade> Upgrades;
};