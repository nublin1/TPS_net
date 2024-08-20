// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TPS/TPSMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Custom_Common/UBUIWButton.h"

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
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UTPSMenuWidget::OnMainMenuButtonCliked()
{
	FName LevelName = FName("Map_MainMenu");
	UGameplayStatics::OpenLevel(this, LevelName);
}

void UTPSMenuWidget::OnQuitButtonClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}
