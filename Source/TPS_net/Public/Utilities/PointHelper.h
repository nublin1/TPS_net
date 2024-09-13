// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PointHelper.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TPS_NET_API UPointHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PointHelper",  meta = (WorldContext="WorldContextObject"))
	static void DrawPoints(UObject* WorldContextObject, TArray<FVector>Points, float PointSize = 10.0f, FColor PointColor= FColor::Red)
	{
		for (const FVector& t_Point : Points)
		{
			DrawDebugPoint(WorldContextObject->GetWorld(), t_Point, PointSize, PointColor, false, 50, 0);
		}
	}
	
	UFUNCTION()
	static void GeneratePointsAlongLine(TArray<FVector>& Points, const FVector& Start, const FVector& End, const int32 PointsPerSide)
	{
		for (int32 i = 0; i < PointsPerSide; ++i)
		{
			float Alpha = static_cast<float>(i) / (PointsPerSide - 1);
			FVector Point = FMath::Lerp(Start, End, Alpha);
			Points.Add(Point);
		}
	}
	
	UFUNCTION(BlueprintCallable, Category = "PointHelper")
	static TArray<FVector> CalculateRectanglePointsFromCollision(AActor* TargetObject, int32 PointsPerSide = 5,	float PointOffset = 50)
	{
		if (!TargetObject)
		{
			return TArray<FVector>();
		}
		
		UStaticMeshComponent* StaticMeshComponent = TargetObject->FindComponentByClass<UStaticMeshComponent>();
		if (!StaticMeshComponent || !StaticMeshComponent->GetStaticMesh())
		{
			return TArray<FVector>();
		}

		TArray<FVector> Points_temp;
		auto TargetLocation = TargetObject->GetActorLocation();

		// Получение размеров коллайдера
		FVector BoxExtent = StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent;
		float Width = BoxExtent.X * 2.0f;  // Ширина прямоугольника
		float Height = BoxExtent.Y * 2.0f; // Высота прямоугольника
		float HalfWidth = Width / 2.0f + PointOffset;
		float HalfHeight = Height / 2.0f + PointOffset;

		FVector TopLeft = TargetLocation + FVector(-HalfWidth, -HalfHeight, 0.0f);
		FVector TopRight = TargetLocation + FVector(HalfWidth, -HalfHeight, 0.0f);
		FVector BottomLeft = TargetLocation + FVector(-HalfWidth, HalfHeight, 0.0f);
		FVector BottomRight = TargetLocation + FVector(HalfWidth, HalfHeight, 0.0f);
		
		//GeneratePointsAlongLine(Points_temp, TopLeft, TopRight, PointsPerSide);   // Верхняя сторона
		GeneratePointsAlongLine(Points_temp, TopRight, BottomRight, PointsPerSide); // Правая сторона
		//GeneratePointsAlongLine(Points_temp, BottomRight, BottomLeft, PointsPerSide);// Нижняя сторона
		//GeneratePointsAlongLine(Points_temp, BottomLeft, TopLeft, PointsPerSide); // Левая сторона
		
		return Points_temp;
	}
};
