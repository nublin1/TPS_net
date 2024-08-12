// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GSChatInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatMessageSendToGS, const FString&, Sender, const FString&, Message);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UGSChatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPS_NET_API IGSChatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual FOnChatMessageSendToGS& GetOnChatMessageSendToGSDelegate() = 0;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BindToChatMessage(UObject* Object, FName FunctionName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SendChatMessage(const FString& Sender, const FString& Message);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================

};

