// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Weapon/WeaponData.h"
#include "Engine/TimerHandle.h"
#include "WeaponSystemComponent.generated.h"


class UCameraComponent;
struct FGameplayTag;
class IProjectileFactory;
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
	Shoot			UMETA(DisplayName = "Shoot"),
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

	UFUNCTION(BlueprintCallable)
	void PreShoot();
	UFUNCTION(BlueprintCallable)
	bool CheckIsCanShoot();
	UFUNCTION(BlueprintCallable)
	void Shoot();
	UFUNCTION()
	void ShootProjectile() const;

	//Getters
	FTransform GetLeftHandSocketTransform() const {return LeftHandSocketTransform;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//
	UPROPERTY()
	TScriptInterface<IProjectileFactory> ProjectileFactory;
	
	//
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
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite )
	EWeaponInteraction WeaponInteraction = EWeaponInteraction::None;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool bIsSwitchingWeapon = false;

	// Player Data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* PlayerCamera;
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(BlueprintReadWrite)
	EHolsterWeaponType LastUsedHolsterType = EHolsterWeaponType::None;

	//Left Hand Helpers
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LeftHandSocketName = "LeftHandSocket";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform LeftHandSocketTransform;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator AimOffset;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNeedCalculateShootInfo = false;
	UPROPERTY()
	bool bIsReadyToNextShoot = true;
	UPROPERTY()
	uint8 AvailableShootsCount = 0;
	UPROPERTY()
	FTimerHandle ShootDelayTimerHandle;


	
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

	UFUNCTION()
	void SwitchStateMachine_Aiming(const FGameplayTag& NewStateTag);

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
};
