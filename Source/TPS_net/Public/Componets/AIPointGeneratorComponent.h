// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIPointGeneratorComponent.generated.h"


class UPointArrayObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API UAIPointGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UAIPointGeneratorComponent();

	UFUNCTION(BlueprintCallable)
	virtual void GeneratePointArray();
	UFUNCTION(BlueprintCallable)
	virtual UPointArrayObject* GetPointsArray() {return PointsArray;}
	UFUNCTION(BlueprintCallable)
	virtual FVector GetRandomPointInArray();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	TObjectPtr<UPointArrayObject> PointsArray;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void OnComponentCreated() override;
	virtual void BeginPlay() override;


		
};
