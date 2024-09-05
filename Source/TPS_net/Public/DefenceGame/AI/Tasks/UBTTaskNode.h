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

UCLASS()
class UPointArrayStructKey : public UBlackboardKeyType_Object
{
	GENERATED_BODY()

public:
	UPointArrayStructKey(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{
		BaseClass = UPointArrayObject::StaticClass();
	}
};

/**
 * 
 */
UCLASS()
class TPS_NET_API UUBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UUBTTaskNode();
	
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
