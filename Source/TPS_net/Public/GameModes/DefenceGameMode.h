// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefenceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API ADefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	ADefenceGameMode();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	int32 AlivePlayersCount;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void BeginPlay() override;
	
};
