// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Custom_Common/UBUIWButton.h"
#include "UI/MainMenu/OptionsMenuWidget.h"
#include "UI/MainMenu/StartGameWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor=true;
	const FInputModeUIOnly InputMode;
	PlayerController->SetInputMode(InputMode);

	if (Start_Button && Start_Button->GetMainButton())
	{
		Start_Button->GetMainButton()->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
	}

	if (Settings_Button)
	{
		Settings_Button->GetMainButton()->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsButtonClicked);
	}

	if (Quit_Button)
	{
		Quit_Button->GetMainButton()->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);
	}

	if (WBP_StartGame && WBP_StartGame->GetBack_Button())
	{
		 WBP_StartGame->GetBack_Button()->GetMainButton()->OnClicked.AddDynamic(this, &UMainMenuWidget::OnInStartGameBackButtonClicked);
	}
}

void UMainMenuWidget::OnStartButtonClicked()
{
	SW_MainMenu->SetActiveWidgetIndex(1);
	
	
}

void UMainMenuWidget::OnSettingsButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
	if (OptionsMenuWidget)
	{
		OptionsMenuWidget->SetVisibility(ESlateVisibility::Visible);
		OptionsMenuWidget->SetPrevActiveWidget(this);
	}
	
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
	//FGenericPlatformMisc::RequestExit(true);
}

void UMainMenuWidget::OnInStartGameBackButtonClicked()
{
	SW_MainMenu->SetActiveWidgetIndex(0);
}
