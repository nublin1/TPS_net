// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "MasterWeaponMelee.generated.h"

UCLASS()
class TPS_NET_API AMasterWeaponMelee : public ABaseWeapon
{
	GENERATED_BODY()
	
#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartAttackSignature);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopAttackSignature);
	
#pragma endregion

public:
	AMasterWeaponMelee();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStartAttackSignature OnStartAttackSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStopAttackSignature OnStopAttackSignature;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void InitWeaponBaseData(UWeaponDataAsset* NewWeaponDataAsset) override;
	virtual void UpdateVisual() override;

	virtual void SwitchAttackMode() override;

	virtual bool IsCanStartReload() override {return false;}

	virtual void InitializeAttackSequence() override;
	virtual void StopAttackSequence() override;

	virtual FAttackReadyResult CheckIsCanAttack() override;

	virtual void AttackTrigger() override;
	virtual void AimTrigger() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsReadyToNextAttack = true;
	
	// Timer
	UPROPERTY()
	FTimerHandle AttackDelayTimerHandle;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartFire();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();
};
