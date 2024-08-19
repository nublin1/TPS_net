// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TPS/AmmoWidget.h"

#include "Components/TextBlock.h"
#include "Player/Components/WeaponSystemComponent.h"
#include "Player/Interfaces/WeaponSystemInterface.h"
#include "World/Weapons/MasterWeapon.h"

UAmmoWidget::UAmmoWidget()
{
}

void UAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAmmoWidget::SighUp()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
	
	APawn* OwningPawn = GetOwningPlayer()->GetPawn();
	if (!OwningPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("OwningPawn is null. Cannot proceed with weapon system setup."));
		return;
	}
	
	if (!OwningPawn->GetClass()->ImplementsInterface(UWeaponSystemInterface::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("OwningPawn does not implement IWeaponSystemInterface."));
		return;
	}
	
	IWeaponSystemInterface* WeaponSystemInterface = Cast<IWeaponSystemInterface>(OwningPawn);
	if (!WeaponSystemInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast OwningPawn to IWeaponSystemInterface."));
		return;
	}

	UWeaponSystemComponent* WeaponSystemComponent = WeaponSystemInterface->GetWeaponSystemComponent();
	if (!WeaponSystemComponent)
		return;

	WeaponSystemComponent->OnShootDelegate.AddDynamic(this, &UAmmoWidget::SetCurrentAmmo);
	WeaponSystemComponent->OnTakeupArmsDelegate.AddDynamic(this, &UAmmoWidget::UAmmoWidget::RefreshWeaponDetails);
	WeaponSystemComponent->OnCompleteReloadDelegate.AddDynamic(this, &UAmmoWidget::RefreshWeaponDetails);
	WeaponSystemComponent->OnHideArmsDelegate.AddDynamic(this, &UAmmoWidget::CollapseWidget);

	
}

void UAmmoWidget::SetCurrentAmmo(int32 RoundsInMagazine)
{
	if (CurrentAmmo)
		CurrentAmmo->SetText(FText::AsNumber(RoundsInMagazine));
}

void UAmmoWidget::RefreshWeaponDetails(AMasterWeapon* WeaponInfo)
{
	if (CurrentAmmo)
		CurrentAmmo->SetText(FText::AsNumber(WeaponInfo->GetRoundsInMagazine()));
	
	if(MaxMagazineAmmo)
		MaxMagazineAmmo->SetText(FText::AsNumber(WeaponInfo->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().MagazineSize));

	this->SetVisibility(ESlateVisibility::Visible);
}

void UAmmoWidget::CollapseWidget()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}