// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "World/Weapons/BaseWeapon.h"
#include "AmmoWidget.generated.h"

class UWeaponSystemComponent;
enum class EFireMode : uint8;
class AMasterWeaponRanged;
class UWeaponBase;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TPS_NET_API UAmmoWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UAmmoWidget();

	UFUNCTION()
	virtual void SetFireMode(EFireMode newFireMode);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	TObjectPtr<UWeaponSystemComponent> WeaponSystemComponent;
	
	UPROPERTY()
	TObjectPtr<UTextBlock> CurrentAmmo;
	UPROPERTY()
	TObjectPtr<UTextBlock> MaxMagazineAmmo;
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> FireMode;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SighUp();

	UFUNCTION()
	void SetCurrentAmmo(int32 RoundsInMagazine);
	UFUNCTION()
	void RefreshWeaponDetails(ABaseWeapon* WeaponInfo);
	UFUNCTION()
	void ClearWeaponDetails(ABaseWeapon* WeaponInfo);
	UFUNCTION()
	void CollapseWidget();
};
