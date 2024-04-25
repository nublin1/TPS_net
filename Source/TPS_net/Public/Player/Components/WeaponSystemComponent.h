// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Weapon/WeaponData.h"
#include "WeaponSystemComponent.generated.h"


enum class EHolsterWeaponType : uint8;
class UWeaponBase;
enum class EWeaponType : uint8;
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

	UFUNCTION(BlueprintCallable)
	bool bIsAnyWeaponInHands() const;
	
	UFUNCTION()
	bool bCheckHolsterAvaibility(EWeaponType BeingCheckedType) const; // true mean available

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AMasterWeapon* CurrentWeaponInHands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HandWeaponSocketName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AMasterWeapon* WeaponPistolHolster;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Blueprintable)
	AMasterWeapon* WeaponPrimaryHolster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> StartingWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSwitchingWeapon = false;

	//Data
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(BlueprintReadWrite)
	EHolsterWeaponType LastUsedHolsterType = EHolsterWeaponType::None;
	

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void InitStartingWeapon();
	UFUNCTION(BlueprintCallable)
	virtual void AddWeapon(UWeaponBase* NewWeaponData);
	UFUNCTION(BlueprintCallable)
	virtual void AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, UWeaponBase* NewWeaponData);
	UFUNCTION(BlueprintCallable)
	virtual void TakeupArms(EHolsterWeaponType Holster = EHolsterWeaponType::None);
	UFUNCTION(BlueprintCallable)
	virtual void HideWeapon();

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
