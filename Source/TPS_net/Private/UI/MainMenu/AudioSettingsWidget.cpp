// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/AudioSettingsWidget.h"

#include "UI/Custom_Common/SettingsOptionSliderRow.h"

void UAudioSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (OptionMasterValue)
	{
		OptionMasterValue->InitializeOption(FText::FromString("MasterValue"), 100);
	}
}
