// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Componets/Weapon/WeaponSystemHelper.h"
#include "Data/Weapon/WeaponData.h"
#include "Factories/ProjectileFactory.h"
#include "GameFramework/Actor.h"
#include "MasterWeaponRanged.generated.h"

class UAmmoBase;
struct FAmmoCharacteristics;
class UCameraComponent;
class UWeaponRanged;


UCLASS()
class TPS_NET_API AMasterWeaponRanged : public ABaseWeapon
{
	GENERATED_BODY()

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnedProjectileSignature, int32, RoundsInMagazine);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartFireSignature);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopFireSignature);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchFireMode, EFireMode, FireMode);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteReloadSignature, int, RoundsInMagazine);
#pragma endregion

public:
	AMasterWeaponRanged();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FOnCompleteReloadSignature OnCompleteReloadDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnSpawnedProjectileSignature OnSpawnedProjectile;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStartFireSignature OnStartFireSignatureDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStopFireSignature OnStopFireDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSwitchFireMode OnSwitchFireModeDelegate;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================	
	virtual void InitWeaponBaseData(UWeaponDataAsset* NewWeaponDataAsset) override;	
	virtual void UpdateVisual() override;

	virtual FVector GetProjectileSpawnLocation() override;

	virtual bool IsCanStartReload() override;
	virtual void StartReload() override;
	virtual FAttackReadyResult CheckIsCanAttack() override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeFireSequence ();
	UFUNCTION(BlueprintCallable)
	void StopFireSequence();
	
	virtual void SwitchAttackMode()override;
	virtual void InitializeAttackSequence() override;
	virtual void StopAttackSequence() override;

	virtual void AttackTrigger(TSubclassOf<UGameplayAbility> AbilityClass) override;

	virtual void AimTrigger() override;

	UFUNCTION()
	void StartFireWeapon();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayReloadAnimation();
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartFire();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();
	UFUNCTION(BlueprintImplementableEvent)
	void OnStopFire();

	UFUNCTION()
	void ConfigureSpawnedProjectile() ;
	UFUNCTION(Server, Unreliable)
	void ServerProjectileSpawn(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FAmmoCharacteristics& AmmoCharacteristics);
	UFUNCTION()
	void HandleProjectileSpawn(const FVector& SpawnLocation, const FRotator& SpawnRotation);

	UFUNCTION(BlueprintCallable)
	void PlayShootEffect(UParticleSystem* ParticleSystem, FName SocketName);
	UFUNCTION(Server, Unreliable)
	void PlayShootEffect_Server(UParticleSystem* ParticleSystem, FName SocketName);
	UFUNCTION(NetMulticast, Unreliable)
	void PlayShootEffect_Multicast(UParticleSystem* ParticleSystem, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void DecreaseRoundsInMagazine();
	UFUNCTION(Server, Unreliable)
	void ServerDecreaseRoundsInMagazine();
	
	UFUNCTION(Server, Unreliable)
	void ServerReload();
	UFUNCTION(BlueprintCallable)
	virtual void SwitchFireMode();

	//Getters
	UFUNCTION(BlueprintCallable)
	EFireMode GetSelectedFireMode() {return SelectedFireMode;}
	UFUNCTION()
	uint16 GetRoundsInMagazine() const {return RoundsInMagazine;}
	UFUNCTION()
	uint16 GetMagazineSize() const {return WeaponDataAssetRef->CharacteristicsOfRangedWeapon.MagazineSize;}
	UFUNCTION()
	bool GetIsStartShooting() {return bIsStartShooting;}

	//
	virtual void SetWeaponBaseRef(UWeaponDataAsset* NewWeaponDataAsset) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ClipBoneName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseBulletActor> BulletActorClass;
	UPROPERTY()
	TScriptInterface<IProjectileFactory> ProjectileFactory;
	
	
	//ShootData
	UPROPERTY()
	bool bIsReadyToNextShoot = true;
	UPROPERTY()
	uint16 AvailableShootsCount = 0;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	bool bIsStartShooting = false;
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_RoundsInMagazine)
	uint16 RoundsInMagazine = 10;
	UPROPERTY(Replicated, BlueprintReadOnly)
	EFireMode SelectedFireMode = EFireMode::None;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UAmmoBase>> UsableAmmo;	
	

	// Recoil
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRecoiling = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentRecoilTime;
		
	//====================================================================
	// FUNCTIONS
	//===================================================================
	UFUNCTION()
	void OnRep_RoundsInMagazine() const;

	UFUNCTION(BlueprintCallable)
	FTransform GetMuzzleTransform(FName SocketName, USceneComponent* OverrideComponent = nullptr);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowTrajectory();

};
