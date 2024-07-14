#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AmmoData.generated.h"


USTRUCT()
struct TPS_NET_API FAmmoCharacteristics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Ammo Characteristics")
	FName Name = "";

	UPROPERTY(EditAnywhere, Category = "Ammo Characteristics")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Ammo Characteristics")
	float BulletMass = 0.100f; // kilograms
};

USTRUCT(Blueprintable, meta=(ScriptName="FAmmoData"))
struct TPS_NET_API FAmmoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Ammo Characteristics")
	FAmmoCharacteristics AmmoCharacteristics;
	
};