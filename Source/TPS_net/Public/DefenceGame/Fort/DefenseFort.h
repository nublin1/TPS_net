// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseFort.generated.h"

class UBoxComponent;

UCLASS()
class TPS_NET_API ADefenseFort : public AActor
{
	GENERATED_BODY()
	
public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	ADefenseFort();

	//Getters
	UFUNCTION()
	TArray<FVector> GetPoints() {return Points;}
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> Points;
	UPROPERTY()
	float PointOffset = 50;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	void DrawPoints(float PointSize = 10.0f, FColor PointColor = FColor::Red);
	TArray<FVector> CalculateRectanglePointsFromCollision(UBoxComponent* BoxComponent, FVector TargetLocation, int32 PointsPerSide);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
