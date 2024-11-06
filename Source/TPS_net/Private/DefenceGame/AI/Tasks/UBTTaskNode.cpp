// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/AI/Tasks/UBTTaskNode.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Utilities/PointHelper.h"

class UPointHelper;

UBTTask_SetTargetPoint::UBTTask_SetTargetPoint()
{
	PointsArray = NewObject<UPointArrayObject>();
}

EBTNodeResult::Type UBTTask_SetTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	bool isNewTarget = BlackboardComp->GetValueAsBool(IsNeedUpdateTargetPoints.SelectedKeyName);
	if (!isNewTarget)
		return EBTNodeResult::Succeeded;

	UObject* TargetObject = BlackboardComp->GetValueAsObject(AITarget.SelectedKeyName);
	AActor* Target = Cast<AActor>(TargetObject);
	if (!Target)
		return EBTNodeResult::Failed;

	if (Target->GetRootComponent()->Mobility == EComponentMobility::Movable)
	{
		return EBTNodeResult::Succeeded;
	}

	UBoxComponent* BoxCollision = Target->FindComponentByClass<UBoxComponent>();

	auto Points = UPointHelper::CalculateRectanglePointsFromCollision(Target, BoxCollision? PointGenerationPattern_Box : PointGenerationPattern_Circle);
	if (Points.Num() <= 0)
		return EBTNodeResult::Failed;

	if (PointsArray == nullptr)
		PointsArray = NewObject<UPointArrayObject>();
	
	PointsArray->Points = Points;
	
	
	BlackboardComp->SetValueAsObject(PointArrayStruct.SelectedKeyName, PointsArray);
	UPointHelper::DrawPoints(GetWorld(),PointsArray->Points);
	
	// Random
	int32 RandomIndex = FMath::RandRange(0, Points.Num()-1);

	FVector TargetLocation = PointsArray->Points[RandomIndex];
	BlackboardComp->SetValueAsVector(KeyTargetLocation.SelectedKeyName, TargetLocation);

	BlackboardComp->SetValueAsInt(TEXT("CurrentPointIndex"), RandomIndex);
	// 
	//UE_LOG(LogTemp, Log, TEXT("Selected random point at index %d: %s"), RandomIndex, *TargetLocation.ToString());

	BlackboardComp->SetValueAsBool(IsNeedUpdateTargetPoints.SelectedKeyName, false);

	return EBTNodeResult::Succeeded;
}

void UBTTask_SetTargetPoint::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

//return Super::ExecuteTask(OwnerComp, NodeMemory);
