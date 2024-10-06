// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_TPS.h"

#include "GameplayTagContainer.h"

FOnChatMessageSendToGS& AGS_TPS::GetOnChatMessageSendToGSDelegate()
{
	return OnChatMessageSendToGS;
}

