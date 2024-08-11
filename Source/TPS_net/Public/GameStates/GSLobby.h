// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GSLobby.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMessageSendToGS, FString, Sender, FString, Message);

UCLASS()
class TPS_NET_API AGSLobby : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FOnMessageSendToGS OnMessageSendToGS;

	//====================================================================
	// FUNCTIONS
	//====================================================================

	protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
