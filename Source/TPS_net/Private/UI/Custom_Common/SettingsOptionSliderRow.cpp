// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/SettingsOptionSliderRow.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"

void USettingsOptionSliderRow::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(OptionNameTextBlock && !OptionNameText.IsEmpty())
	{
		OptionNameTextBlock->SetText(OptionNameText);
	}

	CurrentValueSlider->OnValueChanged.AddDynamic(this, &USettingsOptionSliderRow::OnSliderValueChanged);
}

void USettingsOptionSliderRow::NativeConstruct()
{
	Super::NativeConstruct();
}

void USettingsOptionSliderRow::UpdateOptionNameText()
{
	if (OptionNameTextBlock)
		OptionNameTextBlock->SetText(OptionNameText);
}

void USettingsOptionSliderRow::OnSliderValueChanged(float NewValue)
{
	CurrentValueTextBlock->SetText(FText::AsNumber(static_cast<int32>(NewValue)));
}

void USettingsOptionSliderRow::InitializeOption(FText OptionName, uint16 InitialValue)
{
	OptionNameText = OptionName;
	UpdateOptionNameText();

	CurrentValueSlider->SetValue(InitialValue);
	CurrentValueTextBlock->SetText(FText::AsNumber(InitialValue));
	
}
