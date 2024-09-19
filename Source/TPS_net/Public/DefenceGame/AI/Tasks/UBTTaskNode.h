// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UBTTaskNode.generated.h"

UCLASS(BlueprintType)
class UPointArrayObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TArray<FVector> Points;
};



/**
 * 
 */
UCLASS(Blueprintable)
class TPS_NET_API UBTTask_SetTargetPoint  : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector AITarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector PointArrayStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector IsNewTargetKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector KeyTargetLocation;

	
	UBTTask_SetTargetPoint();
	
protected:
	UPROPERTY()
	TObjectPtr<UPointArrayObject> PointsArray;
	
	//
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
