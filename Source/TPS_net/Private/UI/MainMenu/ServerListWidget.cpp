// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/ServerListWidget.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "GameInstance/MultiplayerGameInstance.h"
#include "UI/Custom_Common/ServerInfoRowWidget.h"
#include "UI/Custom_Common/UBUIWButton.h"

void UServerListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RefleshButton)
	{
		RefleshButton->GetMainButton()->OnClicked.AddDynamic(this, &UServerListWidget::OnRefleshButtonClicked);
	}

	if (UMultiplayerGameInstance* GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance()))
	{
		GameInstance->FindSessionsCompleteDelegate.AddDynamic(this, &UServerListWidget::OnFindSessionsComplete);
	}
}

void UServerListWidget::OnRefleshButtonClicked()
{
	if (UMultiplayerGameInstance* GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance()))
	{
		const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (OnlineSubsystem)
		{
			//GameInstance->OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UServerListWidget::OnFindSessionsComplete);
			GameInstance->FindSessions(false, true);
			WS_ServerList->SetActiveWidgetIndex(0);
		}
	}
}

void UServerListWidget::OnFindSessionsComplete(bool bWasSuccessful, TArray<FCustomSessionSearchResult> SessionSearchResult)
{
	// Just debugging the Number of Search results. Can be displayed in UMG or something later on
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearchResult.Num()));
	
	if (SessionSearchResult.Num() > 0)
	{
		ServerListScrool->ClearChildren();
		for (int32 SearchIdx = 0; SearchIdx < SessionSearchResult.Num(); SearchIdx++)
		{
			if (UServerInfoRowWidget* ServerInfoRowWidget = CreateWidget<UServerInfoRowWidget>(
				GetWorld(), ServerInfoRowWidgetClass))
			{
				ServerInfoRowWidget->SetOnlineSession(SessionSearchResult[SearchIdx]);
				ServerInfoRowWidget->UpdateText();
				ServerListScrool->AddChild(ServerInfoRowWidget);
			}
		}
		WS_ServerList->SetActiveWidgetIndex(1);
	}
	else
	{
		WS_ServerList->SetActiveWidgetIndex(2);
	}
}


