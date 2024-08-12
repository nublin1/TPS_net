// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "Chat.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UChat : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UChat();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AddMessage(const FString& Sender,  const FString& Message);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	void SetupChat();
	
};
