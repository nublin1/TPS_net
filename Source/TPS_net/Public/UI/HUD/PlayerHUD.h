// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UGameCoreHUDLayout;
class UMainHUDLayout;
/**
 * 
 */
UCLASS()
class TPS_NET_API APlayerHUD : public AHUD
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
	// Classes
	UPROPERTY(EditAnywhere, Category = "HUDSettings", BlueprintReadWrite)
	TSubclassOf<UMainHUDLayout> MainHUDLayoutWidgetClass;
	
	// Widgets
	UPROPERTY(EditAnywhere, Category = "HUDSettings", BlueprintReadWrite)
	UMainHUDLayout* MainHUDContainer;
	UPROPERTY(EditAnywhere, Category = "HUDSettings", BlueprintReadWrite)
	UGameCoreHUDLayout* GameCoreHudLayout;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
