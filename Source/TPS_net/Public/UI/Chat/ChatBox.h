// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "ChatBox.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UChatBox : public UBUIUserWidget
{
	GENERATED_BODY()

	
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================

	protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadWrite)
	APlayerController* PlayerController;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
