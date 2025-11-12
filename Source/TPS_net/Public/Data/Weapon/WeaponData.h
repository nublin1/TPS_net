// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "RecoilAnimationComponent.h"
#include "Weapon/Bullets/BaseBulletActor.h"
#include "WeaponData.generated.h"


class UCurveVector;
class ABaseBulletActor;

UENUM(BlueprintType, meta=(ScriptName="EWeaponType"))
enum class EWeaponType : uint8
{
	Ranged	UMETA(DisplayName = "Ranged"),
	Melee	UMETA(DisplayName = "Melee"),
	//Unarmed UMETA(DisplayName = "Unarmed")
};

UENUM(BlueprintType, meta=(ScriptName="ERangedWeaponType"))
enum class ERangedWeaponType : uint8
{
	Rifle UMETA(DisplayName = "Rifle"),
	Pistol	UMETA(DisplayName = "Pistol"),
	Shotgun UMETA(DisplayName = "Shotgun"),
	Throw UMETA(DisplayName = "Throw")
};
UENUM(BlueprintType, meta=(ScriptName="EMeleeWeaponType"))
enum class EMeleeWeaponType : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed")
};

UENUM(BlueprintType)
enum class EWeaponGripType : uint8
{
	OneHanded     UMETA(DisplayName = "One-Handed"),
	TwoHanded     UMETA(DisplayName = "Two-Handed")
};

UENUM(BlueprintType, meta=(ScriptName="EHolsterWeaponType"))
enum class EHolsterWeaponType : uint8
{
	None				UMETA(DisplayName = "None"),
	Primary				UMETA(DisplayName = "Primary"),
	AlternativePrimary	UMETA(DisplayName = "AlternativePrimary"),
	Pistol				UMETA(DisplayName = "Pistol"),
	Unarmed				UMETA(DisplayName = "Unarmed")
};

UENUM(Blueprintable, BlueprintType)
enum class EBulletMode : uint8
{
	HitScan		UMETA(DisplayName = "HitScan"),
	Projectile	UMETA(DisplayName = "Projectile"),
};

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	None        = 0   UMETA(DisplayName = "None"),
	Single      = 1   UMETA(DisplayName = "Single"),
	Burst       = 2   UMETA(DisplayName = "Burst"),
	Full_Auto   = 3   UMETA(DisplayName = "Full_Auto"),
};

USTRUCT(BlueprintType)
struct FShootActionData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSpawnFromCamera = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> CharShootAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> ReloadAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlueprint> BulletActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBulletFlightMode BulletFlightMode = EBulletFlightMode::Physical;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BulletSpawnSocketTransformName = "MuzzleFlash";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayBeforeSpawnBullet = 0.0f;
};

USTRUCT(BlueprintType)
struct FWeaponPresentationData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> SkeletalMesh;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> WeaponShootAnimMontage;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimBlueprint* WeaponAnimationBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ClipBoneName = "Clip_Bone";	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<URecoilData> RecoilAnimData;
};

USTRUCT(BlueprintType)
struct FCharacteristicsOfTheWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Characteristics",
		meta = (ToolTip = "Attack radius used by AI to determine strike distance"))
	float AttackRange = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Characteristics")
	TArray<EFireMode> AvailableShootingModes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Characteristics")
	TArray<FDataTableRowHandle> UsableAmmo;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Weapon Characteristics")
	float SpreadAngle = 1.0f;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Weapon Characteristics")
	int ShotsPerBurst = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Characteristics")
	float RPM = 600; //Rounds per minute
	UPROPERTY(EditAnywhere, Category = "Weapon Characteristics")
	bool bInfinityMagazine = false;
	UPROPERTY(EditAnywhere, Category = "Weapon Characteristics", meta=(
		EditCondition = "!bInfinityMagazine" // Условие: редактируется, если bInfinityMagazine == false
	))
	uint16 MagazineSize = 30; // Rounds
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Weapon Characteristics")
	float MuzzleVelocity = 55000; // cm/sec

	FCharacteristicsOfTheWeapon()
	{
		AvailableShootingModes = {EFireMode::Single};
	}
};

USTRUCT(BlueprintType)
struct FCharacteristicsOfTheWeaponMelee
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Melee attack radius used by AI to determine strike distance"))
	float MeleeAttackRange = 150.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDelay = 2.0f;
};

UCLASS(BlueprintType)
class TPS_NET_API UWeaponDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    //====================================================================
    // ОСНОВНЫЕ ДАННЫЕ ОРУЖИЯ (общие)
    //====================================================================
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
    EWeaponType WeaponType = EWeaponType::Ranged;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
    EHolsterWeaponType HolsterWeaponType = EHolsterWeaponType::Primary;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
	FName HolsterName = "HolsterName";

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
    EWeaponGripType WeaponGripType = EWeaponGripType::TwoHanded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
	float WeaponMass = 1.0f; // kilograms

    //====================================================================
    // ДАННЫЕ СТРЕЛКОВОГО ОРУЖИЯ
    //====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged",
	   meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
	ERangedWeaponType RangedWeaponType = ERangedWeaponType::Rifle;
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged",
        meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
    EBulletMode BulletMode = EBulletMode::Projectile;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged",
		meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
	bool ShowTrace = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged",
        meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
    FCharacteristicsOfTheWeapon CharacteristicsOfTheWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged",
	   meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
	bool bAutoReload = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged",
	   meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
	bool bReloadingByCooldown = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CooldownReload = 2.0f;

    //====================================================================
    // ДАННЫЕ БЛИЖНЕГО БОЯ
    //====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Melee",
			meta = (EditCondition = "WeaponType == EWeaponType::Melee", EditConditionHides))
	EMeleeWeaponType MeleeWeaponType = EMeleeWeaponType::Unarmed;
	
	// описание типа урона
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Melee",
        meta = (EditCondition = "WeaponType == EWeaponType::Melee", EditConditionHides))
    float MeleeDamage = 50.0f;
    
    // монтаж для анимации атаки ближнего боя
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Melee",
        meta = (EditCondition = "WeaponType == EWeaponType::Melee", EditConditionHides))
    TObjectPtr<UAnimMontage> MeleeAttackAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Melee",
	   meta = (EditCondition = "WeaponType == EWeaponType::Melee", EditConditionHides))
	FCharacteristicsOfTheWeaponMelee CharacteristicsOfTheWeaponMelee;
    
    //====================================================================
    // АССЕТЫ ОРУЖИЯ (WeaponAssetData)
    //====================================================================
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Asset",
		meta = (EditCondition = "WeaponType != EWeaponType::Unarmed", EditConditionHides))
    FWeaponPresentationData WeaponAssetData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Asset",
		  meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
	FShootActionData ShootActionData;  
};

UCLASS(Blueprintable)
class TPS_NET_API UWeaponHelper : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	static FName ConvertHolsterTypeToText(const EHolsterWeaponType HolsterType)
	{
		switch (HolsterType)
		{
		case EHolsterWeaponType::Primary:
			return FName("PrimaryHolster");
		case EHolsterWeaponType::Pistol:
			return FName("R_PistolHolster");
		case EHolsterWeaponType::None: 
			return FName("Melee");
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
