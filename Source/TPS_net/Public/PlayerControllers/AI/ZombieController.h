// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "ZombieController.generated.h"

class UNavigationSystemV1;
/**
 * 
 */
UCLASS()
class TPS_NET_API AZombieController : public AAIController
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	explicit AZombieController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void StartFollow(AActor* TargetActor, FVector NewTargetLocation, float AcceptanceRadius = 50.0f);
	UFUNCTION(BlueprintCallable)
	void StopFollow();

	//
	UFUNCTION(BlueprintCallable)
	void CheckObstacles(FVector Start, FVector End, float Radius = 45.0f);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	FTimerHandle SeekTimerHandle;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> CurrentTargetActor;
	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation;
	UPROPERTY(blueprintReadOnly)
	TArray<FHitResult> ObstaclesHitResult;

	UPROPERTY(BlueprintReadOnly)
	bool bIsTargetIsReachable = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsMoveCompleted = false;

	UPROPERTY()
	UNavigationSystemV1* NavSystem;
	UPROPERTY()
	UNavigationPath* Path = nullptr;

	UPROPERTY()
	bool IsDebug = false;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void Seek();

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UFUNCTION(BlueprintCallable)
	void TargetDestoyed(AActor* DestroyedActor);
};
