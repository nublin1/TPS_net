// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/SettingsOptionSliderRow.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"

void USettingsOptionSliderRow::InitializeOption(FText OptionName, uint16 InitialValue)
{
	OptionNameTextBlock->SetText(OptionName);
	CurrentValueSlider->SetValue(InitialValue);
	CurrentValueTextBlock->SetText(FText::FromString( FString::FromInt(InitialValue)));
}
