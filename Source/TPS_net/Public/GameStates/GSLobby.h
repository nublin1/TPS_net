// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Interfaces/GSChatInterface.h"
#include "GSLobby.generated.h"


UCLASS()
class TPS_NET_API AGSLobby : public AGameStateBase, public IGSChatInterface
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

	UFUNCTION(BlueprintCallable)
	virtual void BindToChatMessage_Implementation(UObject* Object, FName FunctionName);

	UFUNCTION(BlueprintCallable)
	void SendChatMessage_Implementation(FString Sender, FString Message);

	protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
