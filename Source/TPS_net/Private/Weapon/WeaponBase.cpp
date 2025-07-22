// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

#include "Net/UnrealNetwork.h"

UWeaponBase::UWeaponBase(): WeaponType(EWeaponType::Rifle), HolsterWeaponType(EHolsterWeaponType::Primary),
                            WeaponGripType(), WeaponAssetData(),
                            SelectedAmmoData(nullptr)
{
}

void UWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponBase, NameID);
	DOREPLIFETIME(UWeaponBase, WeaponType);
	DOREPLIFETIME(UWeaponBase, HolsterWeaponType);
	DOREPLIFETIME(UWeaponBase, BulletMode);
	DOREPLIFETIME(UWeaponBase, CharacteristicsOfTheWeapon);
	DOREPLIFETIME(UWeaponBase, WeaponAssetData);
	DOREPLIFETIME(UWeaponBase, UsableAmmo);
	DOREPLIFETIME(UWeaponBase, SelectedAmmoData);
}

