// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TPS/Store/StoreCard.h"

#include "UI/HUD/TPS/Store/StoreCardRowWidget.h"

UStoreCard::UStoreCard()
{
}

void UStoreCard::NativeConstruct()
{
	Super::NativeConstruct();

	/*if (Stack_Rows)
	{
		const TArray<UWidget*> Children = Stack_Rows->GetAllChildren();
		for (UWidget* Child : Children)
		{
			if (TObjectPtr<UStoreCardRowWidget> StoreCardRow = Cast<UStoreCardRowWidget>(Child))
			{
				CardRows.Add(StoreCardRow);
			}
		}
	}*/
}
