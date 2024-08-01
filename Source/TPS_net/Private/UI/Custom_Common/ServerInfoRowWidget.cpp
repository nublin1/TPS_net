// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/ServerInfoRowWidget.h"

#include "Components/TextBlock.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UServerInfoRowWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UServerInfoRowWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	if (UMultiplayerGameInstance* GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance()))
	{
		IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (!OnlineSubsystem)
		{
			return FReply::Unhandled();
		}
		auto PlayerID = OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(0);
		GameInstance->JoinSession(PlayerID, *Session.HostUserName, Session.SearchResult);
	}

	return FReply::Unhandled();
}


void UServerInfoRowWidget::UpdateText()
{
	PlayerName->SetText(FText::FromString(Session.HostUserName));
	Ping->SetText(FText::AsNumber(Session.Ping));

	int32 CurrentPlayers = Session.CurrentPlayers;
	int32 MaxPlayers = Session.MaxPlayers;
	FText PlayersCount = FText::Format(
		FText::FromString("{0} / {1}"),
		FText::AsNumber(CurrentPlayers),
		FText::AsNumber(MaxPlayers)
	);

	NumPlayers->SetText(PlayersCount);
}
