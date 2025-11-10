// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystemHelper.h"
#include "Components/ActorComponent.h"
#include "Data/Weapon/WeaponData.h"
#include "Engine/TimerHandle.h"
#include "Interfaces/StateMachineInterface.h"
#include "WeaponSystemComponent.generated.h"

class ABaseWeapon;
enum class EShootReadyStatus : uint8;
class APlayerCharacter;
class UStateMachineComponent;
class UCameraComponent;
struct FGameplayTag;
class IProjectileFactory;
enum class EHolsterWeaponType : uint8;
class UWeaponBase;
enum class EWeaponType : uint8;
class AMasterWeaponRanged;
class AMasterWeaponMelee;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, BlueprintSpawnable) )
class TPS_NET_API UWeaponSystemComponent : public UActorComponent, public IStateMachineInterface
{
	GENERATED_BODY()

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeupArmsSignature, ABaseWeapon*, TakeupWeaponInHands);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHideArmsSignature,  ABaseWeapon*, HideWeaponInHands);
#pragma endregion

public:
	UWeaponSystemComponent();

protected:
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FOnTakeupArmsSignature OnTakeupArmsDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnHideArmsSignature OnHideArmsDelegate;
	
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
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool bIsAnyWeaponInHands() const;
	
	UFUNCTION()
	bool bCheckHolsterAvaibility(EHolsterWeaponType BeingCheckedType, int NumberOfHolster = 0) const; // true mean available

	UFUNCTION(BlueprintCallable)
	void UpdateSocketsTransform();
	
	UFUNCTION(BlueprintCallable)
	FAttackReadyResult CheckIsCanAttack();
	
	UFUNCTION(BlueprintCallable)
	void TriggerAttack();

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
	ABaseWeapon* GetCurrentWeaponInHands() {return CurrentWeaponInHands;}
	UFUNCTION()
	FTransform GetLeftHandSocketTransform() const {return LeftHandSocketTransform;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UWeaponDataAsset>> StartingWeaponsArray;
	
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoEquipLast = false;
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_CurrentWeaponInHands, VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ABaseWeapon> CurrentWeaponInHands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HandWeaponSocketName = "SocketWeapon";
	UPROPERTY(Replicated, BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<ABaseWeapon> WeaponPistolHolster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfWeaponPrimaryHolsters = 5;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Blueprintable)
	TArray<TObjectPtr<ABaseWeapon>> WeaponPrimaryHolster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfWeaponUnarmedHolsters = 10;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ABaseWeapon>> UnarmedHolster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfWeaponMeleeHolsters = 10;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ABaseWeapon>> MeleeHolster;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMasterWeaponRanged> WeaponClassRanged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMasterWeaponMelee> WeaponClassMelee;
	

	// Player Data
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacterLink = nullptr;
	
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
	bool bIsNeedCalculateShootInfo = false;

	// State
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FGameplayTag CurrentStateTag;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InitialStateTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebug = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FGameplayTag> StateHistory;	
	int StateHistoryLenght = 5;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual void InitStartingWeapon();
	UFUNCTION(BlueprintCallable)
	virtual void AddWeapon(ABaseWeapon* Weapon, int NumberSlot);
	UFUNCTION(Server, Unreliable)
	virtual void ServerAddWeapon(UWeaponDataAsset* WeaponData);
	UFUNCTION(BlueprintCallable)
	virtual void AssignWeaponToHolsterSlot(ABaseWeapon* WeaponInstance, int NumberSlot = 0);
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
