// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Director.generated.h"


class ANPCZombie;

USTRUCT(Blueprintable)
struct FZombieWaves
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	int ZombieCount = 10;
	
	FZombieWaves(){}
	explicit FZombieWaves(const int ZombieCount)
	{
		this->ZombieCount = ZombieCount;
	};
};

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FZombieWaves> ZombieWaves = {FZombieWaves(10) };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ANPCZombie*> Zombies; 
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnZombieKilled(ANPCZombie* KilledActor);

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void Tick(float DeltaTime) override;

};
