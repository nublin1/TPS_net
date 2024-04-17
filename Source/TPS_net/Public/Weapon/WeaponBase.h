// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Weapon/WeaponData.h"
#include "UObject/NoExportTypes.h"
#include "WeaponBase.generated.h"

enum class EHolsterType : uint8;
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
	FName GetID() const { return ID; }

	void SetID(const FName& ID) { this->ID = ID; }

	EHolsterType GetHolsterType() const { return HolsterType; }

	// Setters
	void SetHolsterType(EHolsterType HolsterType) { this->HolsterType = HolsterType; }

	FWeaponAssetData GetWeaponAssetData() const { return WeaponAssetData; }

	void SetWeaponAssetData(const FWeaponAssetData& WeaponAssetData) { this->WeaponAssetData = WeaponAssetData; }

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(VisibleAnywhere, Category = "Weapon Data")
	FName ID;

protected:
	UPROPERTY(VisibleAnywhere)
	EHolsterType HolsterType;

	UPROPERTY(VisibleAnywhere)
	FWeaponAssetData WeaponAssetData;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
