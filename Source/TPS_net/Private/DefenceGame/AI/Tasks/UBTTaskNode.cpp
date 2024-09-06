// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/AI/Tasks/UBTTaskNode.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetTargetFromPoints::UBTTask_SetTargetFromPoints()
{
}

EBTNodeResult::Type UBTTask_SetTargetFromPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		UPointArrayObject* PointsArray =  Cast<UPointArrayObject>(BlackboardComp->GetValueAsObject(TEXT("PointArrayStruct")));
		int32 CurrentIndex = BlackboardComp->GetValueAsInt(TEXT("CurrentPointIndex"));

		if (PointsArray->Points.IsValidIndex(CurrentIndex))
		{
			FVector TargetLocation = PointsArray->Points[CurrentIndex];
			BlackboardComp->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);

			// Увеличьте индекс для следующего вызова
			BlackboardComp->SetValueAsInt(TEXT("CurrentPointIndex"), (CurrentIndex + 1) % PointsArray->Points.Num());

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
}
