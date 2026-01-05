// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "RecoilAnimationComponent.h"
#include "AbilitySystemComponent.h"
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
	Unarmed UMETA(DisplayName = "Unarmed"),
	Axe		UMETA(DisplayName = "Axe"),
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
	First				UMETA(DisplayName = "First"),
	Pistol				UMETA(DisplayName = "Pistol"),
	Primary				UMETA(DisplayName = "Primary"),
	AlternativePrimary	UMETA(DisplayName = "AlternativePrimary"),
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
struct FMovementSpeedConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxWalkSpeed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxWalkSpeedAiming = 250.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxWalkSpeedAttacking = 200.0f;
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
	TObjectPtr<UBlendSpace> BlendSpaceRegular;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> BlendSpaceAiming;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> ReloadAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> TakeUpAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> PutToHolsterAnimMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimBlueprint* WeaponAnimationBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ClipBoneName = "Clip_Bone";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AmmoMeshReloadPosition = "AmmoMesh";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<URecoilData> RecoilAnimData;
};

USTRUCT(BlueprintType)
struct FShootActionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Used by AI to determine strike distance"))
	float MaxAttackRange_AI = 1500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = ""))
	float MaxAttackRange_Tolerance = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Used by AI to determine strike distance"))
	float MinAttackRange_AI = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> CharShootAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> WeaponShootAnimMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseBulletActor> BulletActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBulletFlightMode BulletFlightMode = EBulletFlightMode::Physical;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BulletSpawnSocketTransformName = "MuzzleFlash";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayBeforeSpawnBullet = 0.0f;
};

USTRUCT(BlueprintType)
struct FCharacteristicsOfRangedWeapon
{
	GENERATED_BODY()
	
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
		EditCondition = "!bInfinityMagazine" 
	))
	uint16 MagazineSize = 30; // Rounds

	FCharacteristicsOfRangedWeapon()
	{
		AvailableShootingModes = {EFireMode::Single};
	}
};

USTRUCT(BlueprintType)
struct FWeaponMeleeAttackData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> MeleeAttackAnimMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	bool HaveImpactDamage = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Properties", meta = (EditCondition = "HaveImpactDamage"))
	float ImpactDamage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float TraceRadiusImpact = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bHaveAoeDamage = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Properties", meta = (EditCondition = "bHaveAoeDamage"))
	float AoeDamage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Properties", meta = (EditCondition = "bHaveAoeDamage"))
	float AoeRadius = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Melee attack radius used by AI to determine strike distance"))
	float MeleeAttackRange = 150.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDelay = 2.0f;
};

USTRUCT(BlueprintType)
struct FWeaponAbilityData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponMeleeAttackData WeaponMeleeAttackData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FShootActionData ShootActionData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties|Curves")
	TObjectPtr<UCurveFloat> MovementAllowedCurve;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
	FMovementSpeedConfig MovementSpeedConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Base")
	TMap<TSubclassOf<UGameplayAbility>, FWeaponAbilityData> GrantedAbilities;

	//====================================================================
	// АССЕТЫ ОРУЖИЯ (WeaponAssetData)
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Asset",
		meta = (EditCondition = "WeaponType != EWeaponType::Unarmed", EditConditionHides))
	FWeaponPresentationData WeaponPresentationData;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged", meta = (ToolTip = "Only for player-controlled Pawn", EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
	bool bTraceFromCamera = false;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Asset",
		meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
	FShootActionData ShootActionData;  */
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged",
        meta = (EditCondition = "WeaponType != EWeaponType::Melee", EditConditionHides))
    FCharacteristicsOfRangedWeapon CharacteristicsOfRangedWeapon;

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
