// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobby/CreateLobbyWidget.h"

#include "Components/CheckBox.h"
#include "Components/EditableText.h"
#include "GameInstance/MultiplayerGameInstance.h"
#include "UI/Custom_Common/UBUIWButton.h"

void UCreateLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WBP_CreateServerButton)
	{
		WBP_CreateServerButton->GetMainButton()->OnClicked.AddDynamic(this, &UCreateLobbyWidget::OnCreateServerButtonClicked);
	}
}

void UCreateLobbyWidget::OnCreateServerButtonClicked()
{
	
	FName ServerName = FName(*ServerNameText->GetText().ToString());
	int32 MaxPlayers = 4;
	//int32 MaxPlayers = FCString::Atoi(*MaxPlayersTextBox->GetText().ToString());

	if (UMultiplayerGameInstance* GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance()))
	{
		//GameInstance->CreateServer(ServerName, MaxPlayers, UseLANCheckBox->IsChecked());
	}
}
