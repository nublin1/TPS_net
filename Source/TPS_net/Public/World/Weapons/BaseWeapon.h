// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Componets/Weapon/WeaponSystemHelper.h"
#include "Data/Weapon/WeaponData.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UAmmoBase;
class UCameraComponent;
class UWeaponDataAsset;

UCLASS(Abstract)
class TPS_NET_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReadyToNextShoot);
#pragma endregion

public:
	ABaseWeapon();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintAssignable)
	FOnReadyToNextShoot OnReadyToNextShoot;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void InitWeaponBaseData(UWeaponDataAsset* NewWeaponDataAsset);
	UFUNCTION()
	virtual void UpdateVisual();
	UFUNCTION(BlueprintCallable)
	void ToggleBoneVisibility(FName BoneName);

	UFUNCTION(BlueprintCallable)
	virtual void SwitchAttackMode() PURE_VIRTUAL(ABaseWeapon::SwitchAttackMode,);
	UFUNCTION(BlueprintCallable)
	virtual bool IsCanStartReload() PURE_VIRTUAL(ABaseWeapon::IsCanStartReload, return false; );
	UFUNCTION(BlueprintCallable)
	virtual void StartReload();
	UFUNCTION(BlueprintCallable)
	virtual FAttackReadyResult CheckIsCanAttack() PURE_VIRTUAL(ABaseWeapon::CheckIsCanAttack, return FAttackReadyResult(););
	UFUNCTION(BlueprintCallable)
	virtual void InitializeAttackSequence() PURE_VIRTUAL(ABaseWeapon::InitializeAttackSequence, ); 
	UFUNCTION(BlueprintCallable)
	virtual void StopAttackSequence() PURE_VIRTUAL(ABaseWeapon::StopAttackSequence, );
	UFUNCTION(BlueprintCallable)
	
	virtual void AttackTrigger(TSubclassOf<UGameplayAbility> AbilityClass) PURE_VIRTUAL(AttackTrigger::AttackTrigger, );
	
	UFUNCTION(BlueprintCallable)
	virtual void AimTrigger()  PURE_VIRTUAL(AttackTrigger::AimTrigger, );

	UFUNCTION(BlueprintCallable)
	virtual FVector GetProjectileSpawnLocation();
	UFUNCTION(BlueprintCallable)
	virtual FVector GetAmmoMeshReloadPosition();

	UFUNCTION()
	UWeaponDataAsset* GetWeaponDataAssetRef() const { return WeaponDataAssetRef; }
	UFUNCTION()
	USkeletalMeshComponent* GetSkeletalMeshWeapon() const { return SkeletalMeshWeapon; }
	UFUNCTION()
	USkeletalMeshComponent* GetSkeletalMeshCharacter() const { return SkeletalMeshCharacter; }

	UFUNCTION()
	virtual void SetWeaponOwnerActor(AActor* NewAOwnerActor) {WeaponOwnerActor = NewAOwnerActor;}
	
	UFUNCTION()
	virtual void SetWeaponBaseRef(UWeaponDataAsset* NewWeaponDataAsset);

	UFUNCTION(Blueprintable)
	virtual void SetTargetPoint(FVector NewPoint) {TargetPoint = NewPoint;}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_WeaponDataAssetRef, BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UWeaponDataAsset> WeaponDataAssetRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWeaponDataAsset> StartingWeaponDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> TraceStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> TraceEnd;

	// Refs
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> WeaponOwnerActor = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> OwnerCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshCharacter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimInstance> AnimInstanceCharacter = nullptr;

	//Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bOwnerIsPlayer = false;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAmmoBase> SelectedAmmoData;

	UPROPERTY(BlueprintReadOnly)
	TMap<AActor*, FHitResult> HitTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector TargetPoint = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> CurrentAttackAbilityClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FWeaponAbilityData CurrentAbilityData;
	
	// Timers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle HitDetectTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle ShootDelayTimerHandle;
	UPROPERTY(visibleAnywhere, BlueprintReadWrite)
	FTimerHandle ReloadCooldownTimerHandle;
	UPROPERTY(visibleAnywhere, BlueprintReadWrite)
	FTimerHandle SpawnBulletDelay;

	// Settings
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bShowTrace = false;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void UpdateTracePoints();
	
	UFUNCTION()
	void OnRep_WeaponDataAssetRef();

	UFUNCTION()
	void HitDetect();
	UFUNCTION(BlueprintCallable)
	void HitDetectStart(bool NewShowTrace = false);
	UFUNCTION(BlueprintCallable)
	void HitDetectEnd();
};
