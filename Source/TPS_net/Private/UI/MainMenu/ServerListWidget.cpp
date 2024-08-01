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
		const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (OnlineSubsystem)
		{
			//GameInstance->OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UServerListWidget::OnFindSessionsComplete);
			GameInstance->FindSessions(true, true);
			
		}		
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
			GameInstance->FindSessions(true, true);
			
		}		
	}
}

void UServerListWidget::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("WORK"));
	
	if (UMultiplayerGameInstance* GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance()))
	{
		auto SearchResults = GameInstance->GetSessionSearch()->SearchResults;
		if (SearchResults.Num() > 0)
		{
			ServerListScrool->ClearChildren();
			for (int32 SearchIdx = 0; SearchIdx <SearchResults.Num(); SearchIdx++)
			{
				if (UServerInfoRowWidget* ServerInfoRowWidget = CreateWidget<UServerInfoRowWidget>(GetWorld(), ServerInfoRowWidgetClass))
				{
					ServerInfoRowWidget->SetOnlineSession(SearchResults[SearchIdx]);
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
}
