// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/AI/Service/BTService_ChoseTarget.h"


UBTService_ChoseTarget::UBTService_ChoseTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//NodeName = "My Service";

	bNotifyBecomeRelevant = true;	// necessarily!!!
	//bNotifyCeaseRelevant = true;

	Interval = 0.5f;	// Any value
	RandomDeviation = 0.f;
}

void UBTService_ChoseTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UBTService_ChoseTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
