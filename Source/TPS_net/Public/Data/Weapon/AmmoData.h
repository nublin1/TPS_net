// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AmmoData.generated.h"

UENUM(BlueprintType)
enum class EProjectileLifetimePolicy : uint8
{
	DestroyOnImpact		UMETA(DisplayName = "Destroy On Impact"),
	DestroyOnTimer		UMETA(DisplayName = "Destroy On Timer"),
	ManualDestruction	UMETA(DisplayName = "Manual Destruction"),
};

USTRUCT(Blueprintable)
struct TPS_NET_API FAmmoCharacteristics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties")
	FName Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties")
	bool HaveImpactDamage = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Bullet Properties", meta = (EditCondition = "HaveImpactDamage"))
	float ImpactDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties")
	bool bHaveAoeDamage = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Bullet Properties", meta = (EditCondition = "bHaveAoeDamage"))
	float AoeDamage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Bullet Properties", meta = (EditCondition = "bHaveAoeDamage"))
	float AoeRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties")
	float BulletMass = 0.100f; // kilograms

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties")
	uint8 NumberOfShotsPerRound = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties", meta = (DisplayName = "StartBulletSpeed"))
	float StartBulletSpeed = 75000; // cm/s

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties", meta = (DisplayName = "BulletLifeTime"))
	float BulletLifeTime = 8;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Properties", meta = (DisplayName = "CrossSection"))
	float CrossSection = 0.49f;
};

USTRUCT(BlueprintType)
struct FBulletBehaviour
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	EProjectileLifetimePolicy ProjectileLifetimePolicy = EProjectileLifetimePolicy::DestroyOnImpact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta = (DisplayName = "IsCanRicochet", ToolTip = "Don't work when is true."))
	bool IsCanRicochet = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta = (DisplayName = "IsEffectOfGravity"))
	bool IsEffectOfGravity = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta = (DisplayName = "IsEffectOfDragForce"))
	bool IsEffectOfDragForce = true;
};

USTRUCT(BlueprintType, Blueprintable)
struct FAmmoAssets
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet visual")
	TObjectPtr<UStaticMesh> MeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet visual")
	TArray<TSubclassOf<AActor>> DestroyEffects;
};

USTRUCT(Blueprintable, meta=(ScriptName="FAmmoData"))
struct TPS_NET_API FAmmoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FAmmoCharacteristics AmmoCharacteristics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FBulletBehaviour AmmoBehaviour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FAmmoAssets AmmoAssets;
	
};