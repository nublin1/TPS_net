// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TPS/Store/StoreCardRowWidget.h"

#include "Components/TextBlock.h"
#include "Data/Upgrades/UpgradeData.h"

UStoreCardRowWidget::UStoreCardRowWidget()
{
}

void UStoreCardRowWidget::InitStoreCardRow(FBaseUpgrade BaseUpgrade)
{
	switch (BaseUpgrade.UpgradeType) {
	case EUpgradeType::Damage:
		UpgradeType->SetText(FText::FromString("Damage"));
		UpgradeValue->SetText(FText::AsNumber(BaseUpgrade.DamageValue));
		break;
	case EUpgradeType::MagazineSize:
		UpgradeType->SetText(FText::FromString("MagazineSize"));
		UpgradeValue->SetText(FText::AsNumber(BaseUpgrade.MagazineSizeValue));
		break;
	case EUpgradeType::FireMode:
		UpgradeType->SetText(FText::FromString("FireMode"));
		CurrentValue->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EUpgradeType::AmmoType:
		UpgradeType->SetText(FText::FromString("AmmoType"));
		CurrentValue->SetVisibility(ESlateVisibility::Collapsed);
		break;
	}
}
