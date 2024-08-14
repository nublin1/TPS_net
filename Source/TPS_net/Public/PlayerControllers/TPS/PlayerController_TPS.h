// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PCChatInterface.h"
#include "PlayerController_TPS.generated.h"

class UChatOnScreen;
class UGameCoreHUDLayout;
class UMainHUDLayout;
/**
 * 
 */
UCLASS()
class TPS_NET_API APlayerController_TPS : public APlayerController, public IPCChatInterface
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	APlayerController_TPS();

	UFUNCTION(BlueprintCallable)
	void SendMessageTo_PcGs_Implementation(FString Sender, FString Message);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatOnScreen* ChatOnScreen;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
};
