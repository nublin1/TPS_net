// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TPS/TimerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "DefenceGame/Director/Director.h"

void UTimerWidget::SighUp()
{
	TArray<AActor*> FoundActors;	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirector::StaticClass(), FoundActors);

	
}

void UTimerWidget::UpdateTimerName(FText NewText)
{
	TimerName->SetText(NewText);
}

void UTimerWidget::UpdateTimerText(int32 Minutes, int32 Seconds)
{
	if (TimerBlock)
	{
		// Format the string to show two digits for minutes and seconds
		FString TimerString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		
		TimerBlock->SetText(FText::FromString(TimerString));
	}
}

void UTimerWidget::SetTimerColor(FSlateColor NewColor)
{
	TimerBlock->SetColorAndOpacity(NewColor);
}

void UTimerWidget::StartTimer()
{
	auto RemainingTimeInSeconds = TimerDelay;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, &RemainingTimeInSeconds]()
	{
		RemainingTimeInSeconds--;

		if (RemainingTimeInSeconds <= 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			RemainingTimeInSeconds = 0;
			OnTimerExpired.Broadcast();  
		}

		int32 Minutes = RemainingTimeInSeconds / 60;
		int32 Seconds = RemainingTimeInSeconds % 60;
		
		UpdateTimerText(Minutes, Seconds);
	},
	 1.0f, true);
}

void UTimerWidget::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}