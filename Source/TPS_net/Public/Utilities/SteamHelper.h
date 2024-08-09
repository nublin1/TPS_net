// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SteamHelper.generated.h"


UENUM()
enum EPlayerAvatarSize
{
	PlayerAvatar_Small,
	PlayerAvatar_Medium,
	PlayerAvatar_Large
};


UCLASS()
class TPS_NET_API USteamHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================


	//====================================================================
	// FUNCTIONS
	//====================================================================
	//UFUNCTION(BlueprintCallable)
	//FUniqueNetIdRepl GetSteamID();

	//UFUNCTION()
	//UTexture2D* GetSteamFriendAvatar(uint64 UniqueNetId, EPlayerAvatarSize PlayerAvatarSize);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================


	//====================================================================
	// FUNCTIONS
	//====================================================================
};
