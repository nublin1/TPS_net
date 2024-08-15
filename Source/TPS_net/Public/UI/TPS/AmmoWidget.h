// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "AmmoWidget.generated.h"

class AMasterWeapon;
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

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	TObjectPtr<UTextBlock> CurrentAmmo;
	UPROPERTY()
	TObjectPtr<UTextBlock> MaxMagazineAmmo;
	
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
	void RefreshWeaponDetails(AMasterWeapon* WeaponInfo);
};
