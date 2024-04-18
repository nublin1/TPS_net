// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystemComponent.generated.h"


class UWeaponBase;
enum class EHolsterType : uint8;
class AMasterWeapon;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, BlueprintSpawnable) )
class TPS_NET_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================	
	UWeaponSystemComponent();

	bool bCheckHolsterAvaibility(EHolsterType BeingCheckedType) const; // true mean avaible

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMasterWeapon* CurrentWeaponInHands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMasterWeapon* WeaponPistolHolster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable)
	AMasterWeapon* WeaponPrimaryHolster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> StartingWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMasterWeapon* MasterWeaponTemplate;

	//====================================================================
	// FUNCTIONS
	//====================================================================	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void InitStartingWeapon();

	UFUNCTION(BlueprintCallable)
	virtual void AddWeapon(UWeaponBase* NewWeaponData);

	UFUNCTION(BlueprintCallable)
	virtual void AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, UWeaponBase* NewWeaponData);

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
