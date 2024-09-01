// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Weapon/WeaponData.h"
#include "Engine/TimerHandle.h"
#include "Interfaces/StateMachineInterface.h"
#include "Weapon/WeaponBase.h"
#include "WeaponSystemComponent.generated.h"


class UCameraComponent;
struct FGameplayTag;
class IProjectileFactory;
enum class EHolsterWeaponType : uint8;
class UWeaponBase;
enum class EWeaponType : uint8;
class AMasterWeapon;


UENUM(Blueprintable, BlueprintType)
enum EWeaponTransitionType: uint8
{
	Holster			UMETA(DisplayName = "Holster"),
	SwitchToPrimary UMETA(DisplayName = "Switch to Primary"),
	SwitchToPistol	UMETA(DisplayName = "Switch to Pistol")
};

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShootSignature, int32, RoundsInMagazine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeupArmsSignature, AMasterWeapon*, TakeupWeaponInHands);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideArmsSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteReloadSignature, AMasterWeapon*, ReloadedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchFireMode, EFireMode, FireMode);

#pragma endregion


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, BlueprintSpawnable) )
class TPS_NET_API UWeaponSystemComponent : public UActorComponent, public IStateMachineInterface
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FOnShootSignature OnShootDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnTakeupArmsSignature OnTakeupArmsDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnHideArmsSignature OnHideArmsDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnCompleteReloadSignature OnCompleteReloadDelegate;
	UPROPERTY(BlueprintCallable)
	FOnSwitchFireMode OnSwitchFireModeDelegate;
	
	
	UPROPERTY(BlueprintAssignable)
	FInitStateSignature InitStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FExitStateSignature ExitStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FTickStateSinganture TickStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FStateChangedSignature StateChangedDelegate;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================	
	UWeaponSystemComponent();

	UFUNCTION(BlueprintCallable)
	bool bIsAnyWeaponInHands() const;
	
	UFUNCTION()
	bool bCheckHolsterAvaibility(EWeaponType BeingCheckedType, int NumberOfHolster = 0) const; // true mean available

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

	// State
	UFUNCTION(BlueprintCallable)
	virtual bool SwitchState(FGameplayTag _StateTag) override;
	UFUNCTION()
	virtual void OnRep_CurrentStateTag() override;
	

	//Getters
	// Implement the delegate accessors
	
	virtual FInitStateSignature& OnInitState() override { return InitStateDelegate; }
	virtual FExitStateSignature& OnExitState() override { return ExitStateDelegate; }
	virtual FTickStateSinganture& OnTickState() override { return TickStateDelegate; }
	virtual FStateChangedSignature& OnStateChanged() override { return StateChangedDelegate; }

	UFUNCTION()
	virtual FGameplayTag GetCurrentStateTag() const override { return CurrentStateTag; }
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	virtual FString GetCurrentStateTagName() const override {return CurrentStateTag.ToString();}

	UFUNCTION()
	AMasterWeapon* GetCurrentWeaponInHands() {return CurrentWeaponInHands;}
	UFUNCTION()
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
	FName HandWeaponSocketName = "SocketWeapon";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AMasterWeapon* WeaponPistolHolster;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int NumberOfWeaponPrimaryHolsters = 5;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Blueprintable)
	TArray<TObjectPtr<AMasterWeapon>> WeaponPrimaryHolster;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> StartingWeapons;


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
	UPROPERTY()
	TObjectPtr<UBlueprint> BulletBlueprint;

	// State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGameplayTag CurrentStateTag;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InitialStateTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebug = false;
	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void InitStartingWeapon();
	UFUNCTION(BlueprintCallable)
	virtual AMasterWeapon* AddWeapon(UWeaponBase* NewWeaponData);
	UFUNCTION(BlueprintCallable)
	virtual void AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, int NumberSlot = 0);
	UFUNCTION(BlueprintCallable)
	virtual void TakeupArms(EHolsterWeaponType Holster = EHolsterWeaponType::None, int NumberOfHolster = 0);
	UFUNCTION(BlueprintCallable)
	virtual void HideWeapon();
	
	UFUNCTION(BlueprintCallable)
	virtual bool IsCanStartReload();

	//
	UFUNCTION()
	void SwitchStateMachine_Aiming(const FGameplayTag& NewStateTag);

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;


private:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void InitState() override;
	virtual void TickState(float DeltaTime) const override;
	virtual void ExitState() override;
};
