// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TPS/Store/UpgradesStore.h"

#include "Components/UniformGridPanel.h"
#include "GameModes/DefenceGameMode.h"
#include "UI/HUD/TPS/Store/StoreCard.h"

UUpgradesStore::UUpgradesStore(): StoreCardsHolderRowsNumber(0), StoreCardsHolderCollumsNumber(0)
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
