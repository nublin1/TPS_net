// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TPS/TimerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "DefenceGame/Director/Director.h"


void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTimerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SighUp();
}

void UTimerWidget::SighUp()
{
	ADirector* Director = Cast<ADirector>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirector::StaticClass()));

	if (Director)
	{
		// Подписываемся на событие OnTimeUpdated в Director
		Director->OnTimeUpdated.AddDynamic(this, &UTimerWidget::UpdateTimerText);

		UE_LOG(LogTemp, Warning, TEXT("TimerWidget: Successfully subscribed to Director's OnTimeUpdated event."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TimerWidget: Failed to find Director instance."));
	}
}

void UTimerWidget::UpdateTimerName(FText NewText)
{
	TimerName->SetText(NewText);
}

void UTimerWidget::UpdateTimerText(int RemainingTime)
{
	if (TimerBlock)
	{
		int32 Minutes = RemainingTime / 60;
		int32 Seconds = RemainingTime % 60;
		
		// Format the string to show two digits for minutes and seconds
		FString TimerString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		
		TimerBlock->SetText(FText::FromString(TimerString));
	}
}

void UTimerWidget::SetTimerColor(FSlateColor NewColor)
{
	TimerBlock->SetColorAndOpacity(NewColor);
}


