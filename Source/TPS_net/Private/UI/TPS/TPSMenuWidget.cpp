// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TPS/TPSMenuWidget.h"

#include "GameInstance/MultiplayerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Custom_Common/UBUIWButton.h"

void UTPSMenuWidget::CloseWidget()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->EnableInput(GetWorld()->GetFirstPlayerController());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}

void UTPSMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
		ResumeButton->GetMainButton()->OnClicked.AddDynamic(this, &UTPSMenuWidget::OnResumeButtonClicked);

	if (ToMainMenuButton)
		ToMainMenuButton->GetMainButton()->OnClicked.AddDynamic(this, &UTPSMenuWidget::OnMainMenuButtonCliked);

	if (QuitButton)
		QuitButton->GetMainButton()->OnClicked.AddDynamic(this, &UTPSMenuWidget::OnQuitButtonClicked);
	
}

void UTPSMenuWidget::OnResumeButtonClicked()
{
	CloseWidget();
}

void UTPSMenuWidget::OnMainMenuButtonCliked()
{
	FName LevelName = FName("Map_MainMenu");
	UGameplayStatics::OpenLevel(this, LevelName);

	auto GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance());
	if (GameInstance)
		GameInstance->DestroyCurrentSession();
}

void UTPSMenuWidget::OnQuitButtonClicked()
{
	auto GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance());
	if (GameInstance)
		GameInstance->DestroyCurrentSession();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}
