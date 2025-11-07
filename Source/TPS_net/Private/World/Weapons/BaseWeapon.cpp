// Nublin Studio 2025 All Rights Reserved.


#include "World/Weapons/BaseWeapon.h"


ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);
}

void ABaseWeapon::InitWeaponBaseData(UWeaponDataAsset* NewWeaponDataAsset)
{
}

void ABaseWeapon::UpdateVisual()
{
}

void ABaseWeapon::ToggleBoneVisibility(FName BoneName)
{
	if (!SkeletalMeshWeapon) return;

	if (bool bIsHidden = SkeletalMeshWeapon->IsBoneHiddenByName(BoneName))
	{
		SkeletalMeshWeapon->UnHideBoneByName(BoneName);
	}
	else
	{
		SkeletalMeshWeapon->HideBoneByName(BoneName, PBO_None);
	}
}

void ABaseWeapon::StartReload()
{
}

void ABaseWeapon::SetWeaponBaseRef(UWeaponDataAsset* NewWeaponDataAsset)
{
	WeaponDataAssetRef = NewWeaponDataAsset;
}

void ABaseWeapon::OnRep_WeaponDataAssetRef()
{
	UpdateVisual();
}


