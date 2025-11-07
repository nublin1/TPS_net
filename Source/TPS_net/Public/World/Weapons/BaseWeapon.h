// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Componets/Weapon/WeaponSystemHelper.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UCameraComponent;
class UWeaponDataAsset;

UCLASS(Abstract)
class TPS_NET_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

#pragma region Delegates
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
	virtual void AttackTrigger()  PURE_VIRTUAL(AttackTrigger::StopAttackSequence, );

	UFUNCTION(BlueprintCallable)
	virtual void AimTrigger()  PURE_VIRTUAL(AttackTrigger::AimTrigger, );
	

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
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_WeaponDataAssetRef, BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UWeaponDataAsset> WeaponDataAssetRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UWeaponDataAsset> StartingWeaponDataAsset;

	UFUNCTION()
	void OnRep_WeaponDataAssetRef();

	// Refs
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> WeaponOwnerActor = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> PlayerCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshCharacter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimInstance> AnimInstanceCharacter = nullptr;

	//Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bOwnerIsPlayer = false;
	

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
