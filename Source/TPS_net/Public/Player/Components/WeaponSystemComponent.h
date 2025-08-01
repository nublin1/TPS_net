// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Weapon/WeaponData.h"
#include "Engine/TimerHandle.h"
#include "Interfaces/StateMachineInterface.h"
#include "Weapon/WeaponBase.h"
#include "WeaponSystemComponent.generated.h"

class UStateMachineComponent;
class UCameraComponent;
struct FGameplayTag;
class IProjectileFactory;
enum class EHolsterWeaponType : uint8;
class UWeaponBase;
enum class EWeaponType : uint8;
class AMasterWeapon;


#pragma region Enums
UENUM(BlueprintType)
enum class EShootReadyStatus : uint8
{
	Ready                UMETA(DisplayName = "Ready to Shoot"),            
	NoAmmo               UMETA(DisplayName = "Not Enough Ammo"),           
	ShootDelayActive     UMETA(DisplayName = "Shoot Delay Active"),       
	WeaponNotEquipped    UMETA(DisplayName = "Weapon Not Equipped"),     
	Unknown              UMETA(DisplayName = "Unknown Reason")        
};

UENUM(Blueprintable, BlueprintType)
enum EWeaponTransitionType: uint8
{
	Holster			UMETA(DisplayName = "Holster"),
	SwitchToPrimary UMETA(DisplayName = "Switch to Primary"),
	SwitchToPistol	UMETA(DisplayName = "Switch to Pistol")
};
#pragma endregion Enums
#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnedProjectileSignature, int32, RoundsInMagazine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartFireSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopFireSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeupArmsSignature, AMasterWeapon*, TakeupWeaponInHands);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHideArmsSignature,  AMasterWeapon*, HideWeaponInHands);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteReloadSignature, AMasterWeapon*, ReloadedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchFireMode, EFireMode, FireMode);

#pragma endregion

USTRUCT(BlueprintType)
struct FShootReadyResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	EShootReadyStatus Status;
	
	UPROPERTY(BlueprintReadWrite)
	FString Message;
	
	FShootReadyResult()
		: Status(EShootReadyStatus::Unknown), Message(TEXT(""))
	{}

	explicit FShootReadyResult(EShootReadyStatus InStatus, const FString& InMessage = TEXT(""))
		: Status(InStatus), Message(InMessage)
	{}
};


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
	FOnSpawnedProjectileSignature OnSpawnedProjectile;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStartFireSignature OnStartFireSignatureDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStopFireSignature OnStopFireDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnTakeupArmsSignature OnTakeupArmsDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnHideArmsSignature OnHideArmsDelegate;
	//UPROPERTY(BlueprintAssignable)
	//FOnCompleteReloadSignature OnCompleteReloadDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSwitchFireMode OnSwitchFireModeDelegate;
	
	//
	UPROPERTY(BlueprintAssignable)
	FInitStateSignature InitStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FExitStateSignature ExitStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FTickStateSinganture TickStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FStateChangedSignature OnStateChangedDelegate;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================	
	UWeaponSystemComponent();

	UFUNCTION(BlueprintCallable)
	bool bIsAnyWeaponInHands() const;
	
	UFUNCTION()
	bool bCheckHolsterAvaibility(EHolsterWeaponType BeingCheckedType, int NumberOfHolster = 0) const; // true mean available

	UFUNCTION(BlueprintCallable)
	void UpdateSocketsTransform();

	UFUNCTION(BlueprintCallable)
	void StopFireSequence();
	UFUNCTION(BlueprintCallable)
	void InitializeFireSequence ();
	UFUNCTION(BlueprintCallable)
	FShootReadyResult CheckIsCanShoot();
	UFUNCTION(BlueprintCallable)
	void TriggerFireWeapon();
	UFUNCTION()
	void ConfigureSpawnedProjectile() ;
	UFUNCTION(Server, Unreliable)
	void ServerProjectileSpawn(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FAmmoCharacteristics& AmmoCharacteristics, AActor* Owner = nullptr);
	UFUNCTION()
	void HandleProjectileSpawn(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FAmmoCharacteristics& AmmoCharacteristics, AActor* Owner = nullptr) ;

	UFUNCTION(BlueprintCallable)
	bool IsCanHideWeapon();

	// Stat
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	virtual void SwitchState(FGameplayTag _NewStateTag) override;
	UFUNCTION()
	virtual void OnRep_CurrentStateTag() override;
	

	//Getters
	// Implement the delegate accessors
	
	virtual FInitStateSignature& OnInitState() override { return InitStateDelegate; }
	virtual FExitStateSignature& OnExitState() override { return ExitStateDelegate; }
	virtual FTickStateSinganture& OnTickState() override { return TickStateDelegate; }
	virtual FStateChangedSignature& OnStateChanged() override { return OnStateChangedDelegate; }

	UFUNCTION()
	virtual FGameplayTag GetCurrentStateTag() const override { return CurrentStateTag; }
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	virtual FString GetCurrentStateTagName() const override {return CurrentStateTag.ToString();}

	UFUNCTION()
	AMasterWeapon* GetCurrentWeaponInHands() {return CurrentWeaponInHands;}
	UFUNCTION()
	FTransform GetLeftHandSocketTransform() const {return LeftHandSocketTransform;}
	UFUNCTION()
	bool GetIsStartShooting() {return bIsStartShooting;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//
	UPROPERTY()
	TScriptInterface<IProjectileFactory> ProjectileFactory;
	
	//
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_CurrentWeaponInHands, VisibleAnywhere, BlueprintReadWrite)
	AMasterWeapon* CurrentWeaponInHands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HandWeaponSocketName = "SocketWeapon";
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AMasterWeapon> WeaponPistolHolster;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int NumberOfWeaponPrimaryHolsters = 5;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Blueprintable)
	TArray<TObjectPtr<AMasterWeapon>> WeaponPrimaryHolster;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> StartingWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMasterWeapon> WeaponClass;
	

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
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	bool bIsStartShooting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsNeedCalculateShootInfo = false;
	UPROPERTY()
	bool bIsReadyToNextShoot = true;
	UPROPERTY()
	uint16 AvailableShootsCount = 0;
	UPROPERTY()
	FTimerHandle ShootDelayTimerHandle;
	UPROPERTY(Transient)
	TObjectPtr<UBlueprint> BulletBlueprint;

	// State
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
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
	virtual void AddWeapon(AMasterWeapon* Weapon, int NumberSlot);
	UFUNCTION(Server, Unreliable)
	virtual void ServerAddWEA(FName WeaponName, AActor* ActorFrom);
	UFUNCTION(BlueprintCallable)
	virtual void AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, int NumberSlot = 0);
	UFUNCTION(BlueprintCallable)
	virtual bool CheckHolsterIsEmpty(EHolsterWeaponType Holster = EHolsterWeaponType::None, int NumberOfHolster = 0);
	UFUNCTION(BlueprintCallable)
	virtual void TakeupArms(EHolsterWeaponType Holster = EHolsterWeaponType::None, int NumberOfHolster = 0);
	UFUNCTION(BlueprintCallable)
	virtual void HideWeapon();
	UFUNCTION()
	void AttachWeapon(AActor* ActorToAttach, FName SocketName);

	UFUNCTION()
	void OnRep_CurrentWeaponInHands();
	
	UFUNCTION(BlueprintCallable)
	virtual bool IsCanStartReload();

	//
	UFUNCTION()
	void SwitchStateMachine_Aiming(AActor* Actor, const FGameplayTag& NewStateTag);
	UFUNCTION()
	void InitState_Aiming(const FGameplayTag& NewStateTag);

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;


private:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	TObjectPtr<UStateMachineComponent> OwnerStateMachineComponent_Aiming;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void InitState() override;
	virtual void TickState(float DeltaTime) const override;
	virtual void ExitState() override;
};
