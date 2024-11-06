// Fill out your copyright notice in the Description page of Project Settings.


#include "Componets/AIPointGeneratorComponent.h"

#include "Components/BoxComponent.h"
#include "DefenceGame/AI/Tasks/UBTTaskNode.h"
#include "Utilities/PointHelper.h"

// Sets default values for this component's properties
UAIPointGeneratorComponent::UAIPointGeneratorComponent()
{
	

}


void UAIPointGeneratorComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	GeneratePointArray();
}

void UAIPointGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAIPointGeneratorComponent::GeneratePointArray()
{
	AActor* Target = GetOwner();
	if (!Target)
		return;

	if (Target->GetRootComponent()->Mobility == EComponentMobility::Movable)
	{
		
	}

	UBoxComponent* BoxCollision = Target->FindComponentByClass<UBoxComponent>();

	auto Points = UPointHelper::CalculateRectanglePointsFromCollision(Target, BoxCollision? PointGenerationPattern_Box : PointGenerationPattern_Circle);
	if (Points.Num() <= 0)
		return;

	if (PointsArray == nullptr)
		PointsArray = NewObject<UPointArrayObject>();
	
	PointsArray->Points = Points;
	
	UPointHelper::DrawPoints(GetWorld(),PointsArray->Points);
}

FVector UAIPointGeneratorComponent::GetRandomPointInArray()
{
	if (PointsArray == nullptr)
		GeneratePointArray();
	
	if (PointsArray && PointsArray->Points.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, PointsArray->Points.Num() - 1);
		return PointsArray->Points[RandomIndex];
	}

	return FVector::ZeroVector;
}

