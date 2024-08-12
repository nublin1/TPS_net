// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/GSLobby.h"

FOnChatMessageSendToGS& AGSLobby::GetOnChatMessageSendToGSDelegate()
{
	return OnChatMessageSendToGS;
}

void AGSLobby::BindToChatMessage_Implementation(UObject* Object, FName FunctionName)
{
	if (Object)
	{
		// Привязываем функцию к делегату
		//OnChatMessageSendToGS.AddDynamic(Object, FunctionName);
	}
}

void AGSLobby::SendChatMessage_Implementation(FString Sender, FString Message)
{
	
}
