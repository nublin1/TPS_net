// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PointHelper.generated.h"

UENUM()
enum EPointGenerationPattern
{
	PointGenerationPattern_Box,
	PointGenerationPattern_Circle,
};

/**
 * 
 */
UCLASS(Blueprintable)
class TPS_NET_API UPointHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PointHelper", meta = (WorldContext="WorldContextObject"))
	static void DrawPoints(UObject* WorldContextObject, TArray<FVector> Points, float PointSize = 10.0f,
	                       FColor PointColor = FColor::Red)
	{
		for (const FVector& t_Point : Points)
		{
			DrawDebugPoint(WorldContextObject->GetWorld(), t_Point, PointSize, PointColor, false, 5, 0);
		}
	}

	UFUNCTION()
	static void GeneratePointsAlongLine(TArray<FVector>& Points, const FVector& Start, const FVector& End,
	                                    const int32 PointsPerSide = 5)
	{
		if (PointsPerSide <= 0)
			return;

		for (int32 i = 0; i < PointsPerSide; ++i)
		{
			float Alpha = static_cast<float>(i) / (PointsPerSide - 1);
			FVector Point = FMath::Lerp(Start, End, Alpha);
			Points.Add(Point);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "PointHelper")
	static void GeneratePointsAlongCircle(TArray<FVector>& Points, const FVector& Center, float Radius = 50,
	                                      int32 PointsCount = 6)
	{
		if (PointsCount <= 0)
			return;

		float AngleIncrement = 2 * PI / PointsCount;
		for (int32 i = 0; i < PointsCount; ++i)
		{
			float Angle = i * AngleIncrement;
			FVector Point = Center + FVector(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, 0.0f);
			Points.Add(Point);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "PointHelper")
	static TArray<FVector> CalculateRectanglePointsFromCollision(AActor* TargetObject,
	                                                             EPointGenerationPattern PointGenerationPattern =
		                                                             PointGenerationPattern_Box,
	                                                             int32 PointsPerSide = 5,
	                                                             float PointOffset = 50
	)
	{
		if (!TargetObject)
		{
			return TArray<FVector>();
		}

		UStaticMeshComponent* StaticMeshComponent = TargetObject->FindComponentByClass<UStaticMeshComponent>();
		USkeletalMeshComponent* SkeletalMeshComponent = TargetObject->FindComponentByClass<USkeletalMeshComponent>();
		if ((!StaticMeshComponent || !StaticMeshComponent->GetStaticMesh()) &&
			(!SkeletalMeshComponent || !SkeletalMeshComponent->GetSkinnedAsset()))
		{
			return TArray<FVector>();
		}

		TArray<FVector> Points_temp;
		auto TargetLocation = TargetObject->GetActorLocation();

		FVector BoxExtent; // Prioritize the StaticMeshComponent if it exists, otherwise use SkeletalMeshComponent		
		if (StaticMeshComponent && StaticMeshComponent->GetStaticMesh())
		{
			BoxExtent = StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent;
		}
		else if (SkeletalMeshComponent && SkeletalMeshComponent->GetSkinnedAsset())
		{
			BoxExtent = SkeletalMeshComponent->GetSkinnedAsset()->GetBounds().BoxExtent;
		}

		switch (PointGenerationPattern)
		{
		case PointGenerationPattern_Box:
			{
				// Получение размеров коллайдера
				float Width = BoxExtent.X * 2.0f; // Ширина прямоугольника
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

		case PointGenerationPattern_Circle:

			GeneratePointsAlongCircle(Points_temp, TargetLocation, PointOffset, PointsPerSide);
			return Points_temp;
		}

		return Points_temp;
	}
};
