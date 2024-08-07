// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerLobby.generated.h"

class ULobbyUIWidget;
/**
 * 
 */
UCLASS()
class TPS_NET_API APlayerControllerLobby : public APlayerController
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

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULobbyUIWidget* LobbyUIWidget;

	//====================================================================
	// FUNCTIONS
	//====================================================================
};
