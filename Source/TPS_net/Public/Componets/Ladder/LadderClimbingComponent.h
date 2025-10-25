// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LadderClimbingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TPS_NET_API ULadderClimbingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULadderClimbingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// ===== Default =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Default")
	bool bLadderSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Default")
	bool bMovementTransitioning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Default")
	bool bAnimationPlaying = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Default")
	float AxisValue = 0.0f;

	// ===== Tracing =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Tracing")
	float TracePointSpaceUp = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Tracing")
	float TracePointSpaceDown = -10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Tracing")
	float BarHeightUp = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Tracing")
	float BarHeightDown = -125.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Tracing")
	FVector NextBarLocationUp = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Tracing")
	FVector NextBarLocationDown = FVector::ZeroVector;

	// ===== Speed =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Speed")
	float ClimbUpSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Speed")
	float ClimbUpSpeedSprinting = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Speed")
	float ClimbDownSpeed = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Speed")
	float SlideDownSpeed = 0.25f;

	// ===== Distance =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Distance")
	float DistanceToClimbUp = 70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Distance")
	float DistanceToClimbUpSprinting = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Distance")
	float DistanceToClimbDown = -92.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Distance")
	float DistanceToSlideDown = -72.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Distance")
	float DistanceFromLadderUp = 42.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Distance")
	float DistanceFromLadderDown = 42.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Distance")
	float ExitLadderSlideHeight = 180.0f;

	// ===== Hand / Feet IK =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Hand/Feet IK")
	bool bLadderIK = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Hand/Feet IK")
	FVector IK_RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Hand/Feet IK")
	FVector IK_LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Hand/Feet IK")
	FVector IK_RightFoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Hand/Feet IK")
	FVector IK_LeftFoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Hand/Feet IK")
	float IK_HipOffset = 0.0f;

	// ===== Data =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Data")
	ACharacter* CharacterRef;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Data")
	//ABP_MasterLadder* LadderRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Data")
	FVector SlideDownTraceImpactPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Data")
	bool bCanJumpOnLadder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder Movement|Data")
	bool bJumpingOnLadder;
};
