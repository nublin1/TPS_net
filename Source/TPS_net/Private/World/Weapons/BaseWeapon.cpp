// Nublin Studio 2025 All Rights Reserved.


#include "World/Weapons/BaseWeapon.h"

#include "Data/Weapon/WeaponData.h"


ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshWeapon->SetupAttachment(RootScene);

	StaticMeshWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshWeapon->SetupAttachment(RootScene);
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
	if (!WeaponDataAssetRef)
	{
		UE_LOG(LogTemp, Warning, TEXT(" AMasterWeapon WeaponDataAssetRef is null"));
		return;
	}

	if (WeaponDataAssetRef->WeaponType != EWeaponType::Melee)
	{
		return;
	}

	if (WeaponDataAssetRef->WeaponAssetData.SkeletalMesh)
	{
		SkeletalMeshWeapon->SetSkeletalMesh(WeaponDataAssetRef->WeaponAssetData.SkeletalMesh);
	}
	if (WeaponDataAssetRef->WeaponAssetData.StaticMesh)
	{
		StaticMeshWeapon->SetStaticMesh(WeaponDataAssetRef->WeaponAssetData.StaticMesh);
	}

	if (WeaponDataAssetRef->WeaponAssetData.WeaponAnimationBlueprint)
		SkeletalMeshWeapon->SetAnimInstanceClass(
			WeaponDataAssetRef->WeaponAssetData.WeaponAnimationBlueprint->GetAnimBlueprintGeneratedClass());
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load animation class"));
	}
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


