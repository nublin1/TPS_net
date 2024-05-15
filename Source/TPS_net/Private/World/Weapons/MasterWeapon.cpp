// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Weapons/MasterWeapon.h"

#include "Weapon/WeaponBase.h"


AMasterWeapon::AMasterWeapon(): WeaponBaseRef(nullptr), SkeletalMeshWeapon(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMeshWeapon);	
}

void AMasterWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (WeaponTable && !StartingWeapon.IsNone())
	{
		const FWeaponData* WData = WeaponTable->FindRow<FWeaponData>(StartingWeapon, StartingWeapon.ToString());
		if (WData)
		{
			WeaponBaseRef = NewObject<UWeaponBase>(this, UWeaponBase::StaticClass());
			WeaponBaseRef->SetID(WData->Name);
			WeaponBaseRef->SetBulletMode(WData->BulletMode);
			WeaponBaseRef->SetCharacteristicsOfTheWeapon(WData->CharacteristicsOfTheWeapon);
			WeaponBaseRef->SetWeaponAssetData(WData->WeaponAssetData);
			WeaponBaseRef->SetWeaponType(WData->HolsterType);

			UpdateVisual();
		}			
	}
}

void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();	
}

void AMasterWeapon::UpdateVisual() const
{
	if (!WeaponBaseRef)
		return;
	
	SkeletalMeshWeapon->SetSkeletalMesh(WeaponBaseRef->GetWeaponAssetData().SkeletalMesh);
	
}

void AMasterWeapon::Reload()
{
	RoundsInMagazine = 10;
}

void AMasterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



