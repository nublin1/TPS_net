// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/OptionsMenuWidget.h"

#include "UI/Custom_Common/UBUIWButton.h"

void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Back_Button)
	{
		Back_Button->GetMainButton()->OnClicked.AddDynamic(this, &UOptionsMenuWidget::OnBackButtonClicked);
	}
}

void UOptionsMenuWidget::OnBackButtonClicked()
{
	if (PrevActiveWidget)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);		
		PrevActiveWidget->SetVisibility(ESlateVisibility::Visible);		
	}
}
