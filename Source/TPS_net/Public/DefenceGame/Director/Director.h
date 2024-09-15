// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Director.generated.h"


class ANPCCharacter;

UCLASS()
class TPS_NET_API ADirector : public AActor
{
	GENERATED_BODY()
	
public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	ADirector();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ANPCCharacter*> Zombies; 
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnZombieKilled(ANPCCharacter* KilledActor);

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void Tick(float DeltaTime) override;

};
