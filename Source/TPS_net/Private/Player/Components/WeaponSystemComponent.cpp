// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/WeaponSystemComponent.h"

#include "Data/Weapon/WeaponData.h"
#include "Weapon/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "World/Weapons/MasterWeapon.h"

// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UWeaponSystemComponent::InitStartingWeapon()
{
	if (!WeaponTable)
		return;

	for (auto StartingWeapon : StartingWeapons)
	{
		if (StartingWeapon.IsNone())
			continue;

		FWeaponData* WData = WeaponTable->FindRow<FWeaponData>(StartingWeapon, StartingWeapon.ToString());
		if (!WData)
			continue;

		UWeaponBase* WeaponBase = NewObject<UWeaponBase>(this, UWeaponBase::StaticClass());
		WeaponBase->SetID(WData->Name);
		WeaponBase->SetWeaponAssetData(WData->WeaponAssetData);
		WeaponBase->SetHolsterType(WData->HolsterType);


		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.bNoFail = true;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true ); 
		
		const FVector SpawnLocation{GetOwner()->GetActorLocation()};
		const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);
		AMasterWeapon *Weapon = GetWorld()->SpawnActor<AMasterWeapon>(AMasterWeapon::StaticClass(), SpawnTransform, SpawnParameters);

		
		Weapon->AttachToComponent(SpawnParameters.Owner, AttachRule, UWeaponHelper::ConvertHolsterTypeToText(WeaponBase->GetHolsterType()));
	}

	
}


// Called every frame
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

