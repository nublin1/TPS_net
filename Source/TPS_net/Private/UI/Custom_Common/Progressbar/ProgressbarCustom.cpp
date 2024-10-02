// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Custom_Common/Progressbar/ProgressbarCustom.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"

UProgressbarCustom::UProgressbarCustom(): ProgressBar(nullptr), Icon(nullptr), TextNumbers(nullptr)
{
}

void UProgressbarCustom::NativeConstruct()
{
	Super::NativeConstruct();
}

void UProgressbarCustom::SetProgress(const float Progress) const // From 0 to 1 
{
	ProgressBar->SetPercent(Progress);
}

void UProgressbarCustom::SetFillColor(FLinearColor NewColor)
{
	ProgressBar->SetFillColorAndOpacity(NewColor);
}

void UProgressbarCustom::SetMaxValue(float NewValue)
{
	MaxValue = NewValue;
	UpdateText();
	const float Percent = CurrentValue / MaxValue * 100;
	SetProgress(Percent);
}

void UProgressbarCustom::SetCurrentValue(float NewValue)
{
	CurrentValue = NewValue;
	//UE_LOG(LogTemp, Warning, TEXT("CurrentValue %f"), CurrentValue);
	UpdateText();

	if (CurrentValue < 0)
		SetProgress(0);
	else if (CurrentValue > MaxValue)
		SetProgress(1);
	else
	{
		auto Percent = CurrentValue / MaxValue;
		SetProgress(Percent);
	}
}

void UProgressbarCustom::UpdateText()
{
	if (!TextNumbers)
		return;

	FString CurrentValueString = FString::FromInt(CurrentValue);
	FString MaxValueString = FString::FromInt(MaxValue);

	// Добавляем ведущие нули до длины 3 символа
	while (CurrentValueString.Len() < 3)
	{
		CurrentValueString = "0" + CurrentValueString;
	}
	while (MaxValueString.Len() < 3)
	{
		MaxValueString = "0" + MaxValueString;
	}
	
	FString FormattedText = FString::Printf(TEXT("%s / %s"), *CurrentValueString, *MaxValueString);

	// Обновляем текстовый блок
	TextNumbers->SetText(FText::FromString(FormattedText));
}
