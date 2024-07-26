// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/UBUIWButton.h"

#include "Components/TextBlock.h"

void UUBUIWButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (MainLabel)
	{
		MainLabel->SetText(ButtonText);
	}
}


UUBUIWButton::UUBUIWButton(): bIsToggleButton(false), bIsToggleOn(false)
{
	
}

