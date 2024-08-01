// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/ServerInfoRowWidget.h"

#include "Components/TextBlock.h"

void UServerInfoRowWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UServerInfoRowWidget::UpdateText()
{
	PlayerName->SetText(FText::FromString(OnlineSession.Session.OwningUserName));
	Ping->SetText(FText::AsNumber(OnlineSession.PingInMs));

	int32 CurrentPlayers = OnlineSession.Session.SessionSettings.NumPublicConnections - OnlineSession.Session.NumOpenPublicConnections;
	int32 MaxPlayers = OnlineSession.Session.SessionSettings.NumPublicConnections;
	FText DisplayText = FText::Format(
			   NSLOCTEXT("MultiplayerGameInstance", "PlayerCountFormat", "{0}/{1}"),
			   FText::AsNumber(CurrentPlayers),
			   FText::AsNumber(MaxPlayers)
		   );
}
