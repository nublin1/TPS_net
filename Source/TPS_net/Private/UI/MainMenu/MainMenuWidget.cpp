// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Custom_Common/UBUIWButton.h"
#include "UI/MainMenu/OptionsMenuWidget.h"

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
}

void UMainMenuWidget::OnStartButtonClicked()
{
	FName LevelName = FName("ThirdPersonMap");
	UGameplayStatics::OpenLevel(this, LevelName);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = (false);
	const FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
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
