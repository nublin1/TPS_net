// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Weapon/WeaponData.h"
#include "UObject/NoExportTypes.h"
#include "WeaponBase.generated.h"

enum class EWeaponType : uint8;
/**
 * 
 */
UCLASS(Blueprintable)
class TPS_NET_API UWeaponBase : public UObject
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UWeaponBase();

	// Getters
	UFUNCTION(BlueprintCallable)
	FName GetID() const { return NameID; }
	UFUNCTION()
	FWeaponAssetData GetWeaponAssetData() const { return WeaponAssetData; }
	UFUNCTION(BlueprintCallable)
	EWeaponType GetWeaponType() const { return WeaponType; }

	// Setters
	void SetWeaponType(EWeaponType _HolsterType) { this->WeaponType = _HolsterType; }

	void SetID(const FName& _NameID) { this->NameID = _NameID; }

	void SetWeaponAssetData(const FWeaponAssetData& _WeaponAssetData) { this->WeaponAssetData = _WeaponAssetData; }

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(VisibleAnywhere, Category = "Weapon Data")
	FName NameID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	UPROPERTY(VisibleAnywhere)
	FWeaponAssetData WeaponAssetData;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
