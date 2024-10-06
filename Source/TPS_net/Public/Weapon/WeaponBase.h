// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoBase.h"
#include "Data/Weapon/WeaponData.h"

#include "WeaponBase.generated.h"

enum class EWeaponType : uint8;


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
	EBulletMode GetEBulletMode() const { return BulletMode; }

	UFUNCTION()
	FCharacteristicsOfTheWeapon GetCharacteristicsOfTheWeapon() const { return CharacteristicsOfTheWeapon; }

	UFUNCTION()
 	FWeaponAssetData GetWeaponAssetData() const { return WeaponAssetData; }

	UFUNCTION(BlueprintCallable)
	EWeaponType GetWeaponType() const { return WeaponType; }
	UFUNCTION()
	TArray<UAmmoBase*> GetUsableAmmo() {return UsableAmmo;}
	UFUNCTION()
	UAmmoBase* GetSelectedAmmoData() const { return SelectedAmmoData; }


	// Setters
	UFUNCTION()
	void SetWeaponType(EWeaponType _HolsterType) { this->WeaponType = _HolsterType; }

	UFUNCTION()
	void SetID(const FName& _NameID) { this->NameID = _NameID; }

	UFUNCTION()
	void SetBulletMode(EBulletMode _BulletMode) { BulletMode = _BulletMode; }

	UFUNCTION()
	void SetCharacteristicsOfTheWeapon(const FCharacteristicsOfTheWeapon& _CharacteristicsOfTheWeapon)
	{
		CharacteristicsOfTheWeapon = _CharacteristicsOfTheWeapon;
	}

	UFUNCTION()
	void SetWeaponAssetData(const FWeaponAssetData& _WeaponAssetData) { this->WeaponAssetData = _WeaponAssetData; }
	UFUNCTION()
	void SetUsableAmmo(TArray<UAmmoBase*> NewArray) {UsableAmmo = NewArray;}
	UFUNCTION()
	void SetSelectedAmmoData(UAmmoBase* NewSelectedAmmoData) { this->SelectedAmmoData = NewSelectedAmmoData; }

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(VisibleAnywhere, Category = "Weapon Data")
	FName NameID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere)
	EBulletMode BulletMode = EBulletMode::HitScan;

	UPROPERTY(EditAnywhere)
	FCharacteristicsOfTheWeapon CharacteristicsOfTheWeapon;

	UPROPERTY(VisibleAnywhere)
	FWeaponAssetData WeaponAssetData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UAmmoBase*> UsableAmmo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAmmoBase* SelectedAmmoData;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
