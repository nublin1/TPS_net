// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TPS/Store/UpgradesStore.h"

#include "Components/UniformGridPanel.h"
#include "UI/HUD/TPS/Store/StoreCard.h"

UUpgradesStore::UUpgradesStore()
{
}

void UUpgradesStore::NativeConstruct()
{
	Super::NativeConstruct();

	/*if (StoreCardsHolder)
	{
		const TArray<UWidget*> Children = StoreCardsHolder->GetAllChildren();
		for (UWidget* Child : Children)
		{
			if (TObjectPtr<UStoreCard> StoreCardRow = Cast<UStoreCard>(Child))
			{
				StoreCardArray.Add(StoreCardRow);
			}
		}
	}*/
}
