// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/SettingsOptionRow.h"

#include "Components/TextBlock.h"
#include "UI/Custom_Common/UBUIWButton.h"

void USettingsOptionRow::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(OptionNameTextBlock && !OptionNameText.IsEmpty())
	{
		OptionNameTextBlock->SetText(OptionNameText);
	}
}

void USettingsOptionRow::NativeConstruct()
{
	Super::NativeConstruct();

	if (DecreaseValueButton)
	{
		DecreaseValueButton->GetMainButton()->OnClicked.AddDynamic(this, &USettingsOptionRow::OnDecreaseButtonClicked);
	}
	if (IncreaseValueButton)
	{
		IncreaseValueButton->GetMainButton()->OnClicked.AddDynamic(this, &USettingsOptionRow::OnIncreaseButtonClicked);
	}

}

void USettingsOptionRow::InitializeOption(FText OptionName, uint16 InitialValue, TArray<FText> PossibleValues)
{
	OptionNameText = OptionName;
	CurrentIndex = InitialValue;
	PossibleValuesText.Empty();
	PossibleValuesText = PossibleValues;

	UpdateOptionNameText();
	UpdateCurrentValueText();
}

void USettingsOptionRow::OnDecreaseButtonClicked()
{
	ChangeValue(false);
}

void USettingsOptionRow::OnIncreaseButtonClicked()
{
	ChangeValue(true);
}

void USettingsOptionRow::UpdateOptionNameText() const
{
	if (OptionNameTextBlock)
	{
		OptionNameTextBlock->SetText(OptionNameText);
	}
}

void USettingsOptionRow::UpdateCurrentValueText()
{
	if (CurrentValueTextBlock && PossibleValuesText.IsValidIndex(CurrentIndex))
	{
		CurrentValueTextBlock->SetText(PossibleValuesText[CurrentIndex]);
	}
}

void USettingsOptionRow::ChangeValue(bool bIncrease)
{
	if (bIncrease)
	{
		CurrentIndex = (CurrentIndex + 1) % PossibleValuesText.Num();
	}
	else
	{
		CurrentIndex = (CurrentIndex - 1 + PossibleValuesText.Num()) % PossibleValuesText.Num();
	}
	
	UpdateCurrentValueText();
}
