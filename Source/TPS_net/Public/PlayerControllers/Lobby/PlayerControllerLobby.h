// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PCChatInterface.h"
#include "PlayerControllerLobby.generated.h"

class UChatOnScreen;
class ULobbyUIWidget;
/**
 * 
 */
UCLASS()
class TPS_NET_API APlayerControllerLobby : public APlayerController, public IPCChatInterface
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================


	//====================================================================
	// FUNCTIONS
	//====================================================================
	APlayerControllerLobby();

	UFUNCTION(BlueprintCallable)
	void SendMessageTo_PcGs_Implementation(FString Sender, FString Message);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULobbyUIWidget* LobbyUIWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChatOnScreen* ChatOnScreen;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
