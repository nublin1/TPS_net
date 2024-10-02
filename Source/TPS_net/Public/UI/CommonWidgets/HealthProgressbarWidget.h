// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Custom_Common/Progressbar/ProgressbarCustom.h"
#include "HealthProgressbarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UHealthProgressbarWidget : public UProgressbarCustom
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UHealthProgressbarWidget();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	

	//====================================================================
	// FUNCTIONS
	//====================================================================
	
	virtual void NativeConstruct() override;
};
