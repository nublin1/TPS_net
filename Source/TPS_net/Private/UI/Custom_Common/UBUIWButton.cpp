// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/UBUIWButton.h"

#include "Components/TextBlock.h"


UUBUIWButton::UUBUIWButton(): bIsToggleButton(false), bIsToggleOn(false)
{
	
}

void UUBUIWButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (MainButton)
	{
		MainButton->OnClicked.AddDynamic(this, &UUBUIWButton::HandleButtonClicked);
	}

	if (MainLabel)
	{
		MainLabel->SetText(ButtonText);

		FSlateFontInfo FontInfo = MainLabel->GetFont();
		
		FontInfo.Size =FontSize;
		MainLabel->SetFont(FontInfo);
	}
}

void UUBUIWButton::HandleButtonClicked()
{
	if (bIsToggleButton)
	{
		bIsToggleOn = !bIsToggleOn;
		OnToggleStateChanged.Broadcast(bIsToggleOn);
	}
	else
	{
		if (OnClickedButton.IsBound())
		{
			OnClickedButton.Broadcast();
		}
	}
}
