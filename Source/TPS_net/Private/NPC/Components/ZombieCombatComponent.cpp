// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Components/ZombieCombatComponent.h"

#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UZombieCombatComponent::UZombieCombatComponent(): TargetClass(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ComponentTags.Add(FName("ZombieCombatComponentTag"));
}

void UZombieCombatComponent::PostInitProperties()
{
	Super::PostInitProperties();
	
}

void UZombieCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	/*USceneComponent* RootComp = GetRootComponent();
	if (RootComp)
	{
		EComponentMobility::Type Mobility = RootComp->Mobility;

		if (Mobility == EComponentMobility::Stationary || Mobility == EComponentMobility::Static)
		{
			if (UBoxComponent* BoxComponent = FindComponentByClass<UBoxComponent>())
			{
				CalculateRectanglePointsFromCollision(BoxComponent, this->GetActorLocation(), 6);
				DrawPoints();
			}
		}
	}*/
	
}

void UZombieCombatComponent::DrawPoints(float PointSize, FColor PointColor)
{
	for (const FVector& t_Point : Points)
	{
		DrawDebugPoint(GetWorld(), t_Point, PointSize, PointColor, false, 50, 0);
	}
}

TArray<FVector> UZombieCombatComponent::CalculateRectanglePointsFromCollision( int32 PointsPerSide)
{
	if (!TargetObject)
	{
		return TArray<FVector>();
	}
	
	UBoxComponent* BoxComponent = TargetObject->FindComponentByClass<UBoxComponent>();	
	if (!BoxComponent)
	{
		return TArray<FVector>();
	}

	TArray<FVector> Points_temp;
	auto TargetLocation = TargetObject->GetActorLocation();

	// Получение размеров коллайдера
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
	float Width = BoxExtent.X * 2.0f;  // Ширина прямоугольника
	float Height = BoxExtent.Y * 2.0f; // Высота прямоугольника

	// Определение смещений от центра до углов прямоугольника с дополнительным смещением
	float HalfWidth = Width / 2.0f + PointOffset;
	float HalfHeight = Height / 2.0f + PointOffset;

	// Углы прямоугольника относительно TargetLocation
	FVector TopLeft = TargetLocation + FVector(-HalfWidth, -HalfHeight, 0.0f);
	FVector TopRight = TargetLocation + FVector(HalfWidth, -HalfHeight, 0.0f);
	FVector BottomLeft = TargetLocation + FVector(-HalfWidth, HalfHeight, 0.0f);
	FVector BottomRight = TargetLocation + FVector(HalfWidth, HalfHeight, 0.0f);

	// Функция для добавления точек вдоль стороны прямоугольника
	auto AddPointsAlongLine = [&Points_temp, PointsPerSide](FVector Start, FVector End) {
		for (int32 i = 0; i < PointsPerSide; ++i)
		{
			float Alpha = static_cast<float>(i) / (PointsPerSide - 1);
			FVector Point = FMath::Lerp(Start, End, Alpha);
			Points_temp.Add(Point);
		}
	};

	// Добавление точек вдоль каждой стороны
	//AddPointsAlongLine(TopLeft, TopRight);   // Верхняя сторона
	AddPointsAlongLine(TopRight, BottomRight); // Правая сторона
	//AddPointsAlongLine(BottomRight, BottomLeft); // Нижняя сторона
	//AddPointsAlongLine(BottomLeft, TopLeft);   // Левая сторона

	// Удаление дублирующихся точек на углах
	Points_temp.Sort([](const FVector& A, const FVector& B) { return A.Equals(B, 0.01f) == false; });
	Points = Points_temp;

	DrawPoints();
	return Points;
}


// Called every frame
void UZombieCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

