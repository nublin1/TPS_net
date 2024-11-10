// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TPS/Store/UpgradesStore.h"

#include "Components/UniformGridPanel.h"
#include "GameModes/DefenceGameMode.h"
#include "UI/HUD/TPS/Store/StoreCard.h"

UUpgradesStore::UUpgradesStore()
{
}

void UUpgradesStore::InitUpgradesStore(FUpgrades UpgradesList)
{
	if (UpgradesList.ListOfUpgrades.Num() == 0)
		return;

	if (!StoreCardClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("StoreCardClass is null"));
		return;
	}

	StoreCardsHolder->ClearChildren();

	for (auto UpgradeBase : UpgradesList.ListOfUpgrades)
	{
		auto UpgradeCard = CreateWidget<UStoreCard>(this, StoreCardClass);
		if (!UpgradeCard)
			continue;

		UpgradeCard->InitStoreCard(UpgradeBase);

		StoreCardsHolder->AddChildToUniformGrid(UpgradeCard, 0, 0);
	}
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
