// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/StartGameWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Custom_Common/UBUIWButton.h"


void UStartGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Create_Button)
	{
		Create_Button->GetMainButton()->OnClicked.AddDynamic(this, &UStartGameWidget::OnCreate_ButtonClicked);
	}

	if (Serverlist_Button)
	{
		Serverlist_Button->GetMainButton()->OnClicked.AddDynamic(this, &UStartGameWidget::OnServerlist_ButtonClicked);
	}
}

void UStartGameWidget::OnSingleButtonClicked() const
{
	FName LevelName = FName("ThirdPersonMap");
	UGameplayStatics::OpenLevel(this, LevelName);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = (false);
	const FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	
}

void UStartGameWidget::OnCreate_ButtonClicked()
{
	WS_StartGame->SetActiveWidgetIndex(2);
}

void UStartGameWidget::OnServerlist_ButtonClicked()
{
	WS_StartGame->SetActiveWidgetIndex(1);
}
