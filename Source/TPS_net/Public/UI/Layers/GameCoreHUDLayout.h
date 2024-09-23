// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameCoreHUDLayout.generated.h"

class UBUIUserWidget;
/**
 * 
 */
UCLASS()
class TPS_NET_API UGameCoreHUDLayout : public UUserWidget
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
	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UBUIUserWidget> TimerBlock;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void NativeConstruct() override;
};

