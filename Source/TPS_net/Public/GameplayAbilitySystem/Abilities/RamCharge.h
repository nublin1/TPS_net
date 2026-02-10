// Nublin Studio 2026 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/Abilities/AbilityBase.h"
#include "RamCharge.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API URamCharge : public UAbilityBase
{
	GENERATED_BODY()

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRamHitActor, AActor*, HitActor);
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRamHitWall);

public:
	URamCharge();

	/*UPROPERTY(BlueprintAssignable)
	FRamHitActor OnEnemyHit;
	UPROPERTY(BlueprintAssignable)
	FRamHitWall OnWallHit;*/

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForwardSweepLength = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceInterval = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxChargeDistance = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanseInterval = 0.1f;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle TraceTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle DistanseTimer;
	
public:
	UFUNCTION(BlueprintCallable)
	void StartChargeTrace();
	UFUNCTION(BlueprintCallable)
	void StopChargeTrace();

	UFUNCTION(BlueprintCallable)
	void StartDistanseCheck();
	UFUNCTION(BlueprintCallable)
	void StopDistanseCheck();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RamCharge")
	bool bUniqueHitsPerCharge = true;

	//data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RamCharge")
	FVector ChargeStartLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RamCharge")
	FVector LastLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RamCharge")
	float TravelledDistance = 0.f;
	UPROPERTY()
	TSet<AActor*> HitActorsHistory;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	void DoTrace();
	UFUNCTION()
	void DoDistanseCheck();

	UFUNCTION(BlueprintImplementableEvent, Category = "RamCharge")
	void HitActor(AActor* HitActor);
	UFUNCTION(BlueprintImplementableEvent, Category = "RamCharge")
	void HitWall();
	UFUNCTION(BlueprintImplementableEvent, Category = "RamCharge")
	void HasReachedDistance();
};
