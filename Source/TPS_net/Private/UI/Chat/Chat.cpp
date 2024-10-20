// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Chat/Chat.h"

#include "GameFramework/GameStateBase.h"
#include "Interfaces/GSChatInterface.h"

UChat::UChat()
{
}

void UChat::SetupChat()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState && GameState->GetClass()->ImplementsInterface(UGSChatInterface::StaticClass()))
	{
		if (IGSChatInterface* GSChatInterface = Cast<IGSChatInterface>(GameState))
		{
			GSChatInterface->GetOnChatMessageSendToGSDelegate().AddDynamic(this, &UChat::AddMessage);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState has not Implement ChatInterface"));
	}
}

