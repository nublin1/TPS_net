// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/TPS/PlayerController_TPS.h"

APlayerController_TPS::APlayerController_TPS(): MainHUDContainer(nullptr), GameCoreHudLayout(nullptr),
                                                ChatOnScreen(nullptr)
{
}

void APlayerController_TPS::SendMessageTo_PcGs_Implementation(FString Sender, FString Message)
{
}