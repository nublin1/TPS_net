#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AmmoData.generated.h"


USTRUCT(Blueprintable)
struct TPS_NET_API FAmmoCharacteristics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
	FName Name = "";

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
	float BulletMass = 0.100f; // kilograms

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
	uint8 NumberOfShotsPerRound = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Properties", meta = (DisplayName = "Velocity"))
	FVector Velocity;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta = (DisplayName = "IsCanRicochet"))
	bool IsCanRicochet = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta = (DisplayName = "IsEffectOfGravity"))
	bool IsEffectOfGravity = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta = (DisplayName = "IsEffectOfDragForce"))
	bool IsEffectOfDragForce = true;
};

USTRUCT(Blueprintable, meta=(ScriptName="FAmmoData"))
struct TPS_NET_API FAmmoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Ammo Characteristics")
	FAmmoCharacteristics AmmoCharacteristics;

	UPROPERTY(EditAnywhere, Category = "Ammo Characteristics")
	FBulletBehaviour AmmoBehaviour;
	
};