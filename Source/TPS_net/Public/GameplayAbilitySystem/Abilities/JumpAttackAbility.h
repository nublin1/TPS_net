// Nublin Studio 2026 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/Abilities/AbilityBase.h"
#include "JumpAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UJumpAttackAbility : public UAbilityBase
{
	GENERATED_BODY()

public:
	UJumpAttackAbility();

	UFUNCTION(BlueprintCallable, Category = "Ability|Physics")
	float GetDistanceToGround() const;

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ability|Physics")
	float CalculateJumpForce(FVector Start, FVector End, float Duration, FVector& OutDirection);
	
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Attack")
	float PredictionTime = 0.2f;

	FTimerHandle TickTimerHandle;


	//
	UFUNCTION(blueprintCallable, Category = "Ability|Physics")
	void StartMonitoringLanding();
	UFUNCTION(blueprintCallable, Category = "Ability|Physics")
	void StopMonitoringLanding();
	void MonitorLandingProgress();
	float GetDynamicPredictDistance(float InPredictionTime) const;
	bool ShouldTriggerLandingDynamic(float InPredictionTime);

	// Событие, которое мы вызовем в Блюпринт, когда пора приземляться
	UFUNCTION(BlueprintImplementableEvent, Category = "Jump Attack")
	void OnLandingPredicted();
};
