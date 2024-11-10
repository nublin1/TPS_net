// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TPS/Store/StoreCard.h"

#include "UI/HUD/TPS/Store/StoreCardRowWidget.h"
#include "UI/HUD/TPS/Upgrade/UpgradeBase.h"

UStoreCard::UStoreCard()
{
}

void UStoreCard::InitStoreCard(UUpgradeBase* UpgradeBase)
{
	if (UpgradeBase == nullptr)
		return;

	if (!CardRowsClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("CardRowsClass is null"));
		return;
	}

	Stack_Rows->ClearChildren();

	for (auto UpRow : UpgradeBase->GetUpgrade())
	{
		auto UpgradeRow = CreateWidget<UStoreCardRowWidget>(this, CardRowsClass);
		if (UpgradeRow == nullptr)
			continue;
		
		UpgradeRow->InitStoreCardRow(UpRow);
	}
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
