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
	UFUNCTION(BlueprintCallable)
	EHolsterWeaponType GetHolsterWeaponType() const { return HolsterWeaponType; }
	UFUNCTION()
	TArray<UAmmoBase*> GetUsableAmmo() {return UsableAmmo;}
	UFUNCTION()
	UAmmoBase* GetSelectedAmmoData() const { return SelectedAmmoData; }


	// Setters
	UFUNCTION()
	void SetWeaponType(EWeaponType _WeaponType) { this->WeaponType = _WeaponType; }
	UFUNCTION()
	void SetHolsterWeaponType(EHolsterWeaponType _HolsterType) { this->HolsterWeaponType = _HolsterType; }

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
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Weapon Data")
	FName NameID;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	EHolsterWeaponType HolsterWeaponType;
	

	UPROPERTY(Replicated, EditAnywhere)
	EBulletMode BulletMode = EBulletMode::HitScan;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	FCharacteristicsOfTheWeapon CharacteristicsOfTheWeapon;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	FWeaponAssetData WeaponAssetData;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UAmmoBase>> UsableAmmo;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAmmoBase> SelectedAmmoData;

	//====================================================================
	// FUNCTIONS
	//====================================================================

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
};
