// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "ChatMessage.generated.h"

class UMultiLineEditableTextBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TPS_NET_API UChatMessage : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UChatMessage();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Sender;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Message;


	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	FString UI_Message;
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	FString UI_Sender;

	//====================================================================
	// FUNCTIONS
	//====================================================================

};
