// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/GSChatInterface.h"
#include "GS_TPS.generated.h"



UCLASS()
class TPS_NET_API AGS_TPS : public AGameStateBase, public IGSChatInterface
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FOnChatMessageSendToGS OnChatMessageSendToGS;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual FOnChatMessageSendToGS& GetOnChatMessageSendToGSDelegate() override;

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
};