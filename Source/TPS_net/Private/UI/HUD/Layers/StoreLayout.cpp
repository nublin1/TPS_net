// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/Layers/StoreLayout.h"

#include "Components/CanvasPanel.h"
#include "GameModes/DefenceGameMode.h"
#include "UI/HUD/TPS/Store/UpgradesStore.h"

void UStoreLayout::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MainCanvasPanel)
		return;

	const TArray<UWidget*> Children = MainCanvasPanel->GetAllChildren();
	for (UWidget* Child : Children)
	{
		if (TObjectPtr<UUpgradesStore> StoreCardRow = Cast<UUpgradesStore>(Child))
		{
			UpgradesStore = StoreCardRow;
			break;
		}
	}
		
}
