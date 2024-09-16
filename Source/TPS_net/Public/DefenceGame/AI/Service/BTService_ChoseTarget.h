// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_ChoseTarget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TPS_NET_API UBTService_ChoseTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_ChoseTarget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

