// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDLayout.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UMainHUDLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================


	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable, Category = "UI")
	void AddWidgetToLayout(UUserWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveWidgetFromLayout(UUserWidget* Widget);
	
protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* LayoutContainer;

	//====================================================================
	// FUNCTIONS
	//====================================================================

	virtual void PostInitProperties() override;
	virtual void NativeConstruct() override;
};
