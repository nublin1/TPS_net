// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/SettingsOptionRow.h"

#include "Components/TextBlock.h"

void USettingsOptionRow::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(OptionNameTextBlock && !OptionNameText.IsEmpty())
	{
		OptionNameTextBlock->SetText(OptionNameText);
	}
	if(CurrentValueTextBlock)
	{
		CurrentValueTextBlock->SetText(CurrentValueText);
	}
}

void USettingsOptionRow::NativeConstruct()
{
	Super::NativeConstruct();

	
}
