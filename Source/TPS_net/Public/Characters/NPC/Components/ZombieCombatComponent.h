// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieCombatComponent.generated.h"


class UBoxComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API UZombieCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UZombieCombatComponent();

	//Getters
	UFUNCTION()
	TArray<FVector> GetPoints() {return Points;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> TargetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> TargetObject;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> Points;
	UPROPERTY()
	float PointOffset = 50;

	UPROPERTY(BlueprintReadOnly)
	TMap<AActor*, bool> AlreadyHitTargets;

	UPROPERTY(EditAnywhere)
	bool IsDebug = false;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

	void DrawPoints(float PointSize = 10.0f, FColor PointColor = FColor::Red);
	UFUNCTION(BlueprintCallable)
	TArray<FVector> CalculateRectanglePointsFromCollision(int32 PointsPerSide);

	UFUNCTION( BlueprintCallable)
	bool HitDetect();

	UFUNCTION(BlueprintCallable)
	void ClearAlreadyHitTargets() {AlreadyHitTargets.Empty();}

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	
};
