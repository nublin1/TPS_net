// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/AI/Tasks/UBTTaskNode.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetTargetPoint::UBTTask_SetTargetPoint()
{
}

EBTNodeResult::Type UBTTask_SetTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		UPointArrayObject* PointsArray =  Cast<UPointArrayObject>(BlackboardComp->GetValueAsObject(TEXT("PointArrayStruct")));
		int32 NumPoints = PointsArray->Points.Num();
		if (NumPoints > 0)
		{
			// Генерируем случайный индекс
			int32 RandomIndex = FMath::RandRange(0, NumPoints - 1);

			FVector TargetLocation = PointsArray->Points[RandomIndex];
			BlackboardComp->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);

			// Логируем текущие значения
			UE_LOG(LogTemp, Log, TEXT("Selected random point at index %d: %s"), RandomIndex, *TargetLocation.ToString());

			// Устанавливаем случайный индекс в Blackboard
			BlackboardComp->SetValueAsInt(TEXT("CurrentPointIndex"), RandomIndex);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
}
