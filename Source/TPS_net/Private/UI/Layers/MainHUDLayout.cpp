// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Layers/MainHUDLayout.h"

#include "Components/PanelWidget.h"


void UMainHUDLayout::PostInitProperties()
{
	Super::PostInitProperties();
}

void UMainHUDLayout::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainHUDLayout::AddWidgetToLayout(UUserWidget* Widget)
{
	if (LayoutContainer && Widget)
	{
		LayoutContainer->AddChild(Widget);
	}
}

void UMainHUDLayout::RemoveWidgetFromLayout(UUserWidget* Widget)
{
	if (LayoutContainer && Widget)
	{
		LayoutContainer->RemoveChild(Widget);
	}
}
