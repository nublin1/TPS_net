// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "ZombieController.generated.h"

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

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	FTimerHandle SeekTimerHandle;

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY(BlueprintReadOnly)
	bool bIsMoveCompleted = false;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void Seek();

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
