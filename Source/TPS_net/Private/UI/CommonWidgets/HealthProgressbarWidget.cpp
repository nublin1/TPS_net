// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonWidgets/HealthProgressbarWidget.h"

#include "Player/Components/HealthComponent.h"

UHealthProgressbarWidget::UHealthProgressbarWidget()
{
}

void UHealthProgressbarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AActor* OwnerActor = GetOwningPlayerPawn())
	{
		if (auto Component = Cast<UHealthComponent>(OwnerActor->FindComponentByClass(UHealthComponent::StaticClass())))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Owner has Health Component"));
			SetMaxValue( Component->GetMaxHealth());
			SetCurrentValue( Component->GetHealth());

			Component->OnHealthChangedDelegate.AddDynamic(this, &UHealthProgressbarWidget::SetCurrentValue);
			
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Owner does not have Health Component"));
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
