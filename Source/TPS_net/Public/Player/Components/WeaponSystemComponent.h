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

UENUM(BlueprintType)
enum class EWeaponInteraction : uint8
{
	None            UMETA(DisplayName = "None"),
	Reload          UMETA(DisplayName = "Reload"),
	Switch          UMETA(DisplayName = "Switch"),
};

UENUM(Blueprintable, BlueprintType)
enum EWeaponTransitionType: uint8
{
	Holster			UMETA(DisplayName = "Holster"),
	SwitchToPrimary UMETA(DisplayName = "Switch to Primary"),
	SwitchToPistol	UMETA(DisplayName = "Switch to Pistol")
};

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

	UFUNCTION(BlueprintCallable)
	void UpdateSocketsTransform();

	//Getters
	FTransform GetLeftHandSocketTransform() const {return LeftHandSocketTransform;}

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

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite )
	EWeaponInteraction WeaponInteraction = EWeaponInteraction::None;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool bIsSwitchingWeapon = false;

	//Data
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(BlueprintReadWrite)
	EHolsterWeaponType LastUsedHolsterType = EHolsterWeaponType::None;

	//Left Hand Helpers
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LeftHandSocketName = "LeftHandSocket";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform LeftHandSocketTransform;
	

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
