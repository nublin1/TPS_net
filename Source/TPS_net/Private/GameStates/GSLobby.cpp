// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/GSLobby.h"

FOnChatMessageSendToGS& AGSLobby::GetOnChatMessageSendToGSDelegate()
{
	return OnChatMessageSendToGS;
}

void AGSLobby::BindToChatMessage_Implementation(const UObject* Object, FName FunctionName)
{
	//OnChatMessageSendToGS.AddDynamic(const_cast<UObject*>(Object), FunctionName);
}

void AGSLobby::SendChatMessage_Implementation(FString Sender, FString Message)
{
	
}
