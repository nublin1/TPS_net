// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/WeaponSystemComponent.h"

#include "Data/Weapon/WeaponData.h"
#include "Weapon/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "World/Weapons/MasterWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent(): CurrentWeaponInHands(nullptr), WeaponPistolHolster(nullptr),
                                                  WeaponPrimaryHolster(nullptr),
                                                  WeaponTable(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game startsKO
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UWeaponSystemComponent::bCheckHolsterAvaibility(EHolsterType BeingCheckedType) const
{
	switch (BeingCheckedType)
	{
	case EHolsterType::Primary:
		return WeaponPrimaryHolster == nullptr;

	case EHolsterType::Pistol:
		return WeaponPistolHolster == nullptr;

	default:
		return false;
	}
}

void UWeaponSystemComponent::InitStartingWeapon()
{
	if (!WeaponTable)
		return;

	for (auto StartingWeapon : StartingWeapons)
	{
		if (StartingWeapon.IsNone())
			continue;

		const FWeaponData* WData = WeaponTable->FindRow<FWeaponData>(StartingWeapon, StartingWeapon.ToString());
		if (!WData)
			continue;

		if (bCheckHolsterAvaibility(WData->HolsterType) == false)
			continue;

		UWeaponBase* WeaponBase = NewObject<UWeaponBase>(this, UWeaponBase::StaticClass());
		WeaponBase->SetID(WData->Name);
		WeaponBase->SetWeaponAssetData(WData->WeaponAssetData);
		WeaponBase->SetHolsterType(WData->HolsterType);

		AddWeapon(WeaponBase);
	}
}

void UWeaponSystemComponent::AddWeapon(UWeaponBase* NewWeaponData)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                     EAttachmentRule::SnapToTarget, true);

	const FVector SpawnLocation{GetOwner()->GetActorLocation()};
	const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);
	AMasterWeapon* Weapon = GetWorld()->SpawnActor<AMasterWeapon>(AMasterWeapon::StaticClass(), SpawnTransform,
	                                                              SpawnParameters);
	Weapon->SetWeaponBaseRef(NewWeaponData);
	Weapon->UpdateVisual();

	auto Comp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	Weapon->AttachToComponent(Comp, AttachRule,
	                          UWeaponHelper::ConvertHolsterTypeToText(NewWeaponData->GetHolsterType()));

	AssignWeaponToHolsterSlot(Weapon, NewWeaponData);
	
}

void UWeaponSystemComponent::AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, UWeaponBase* NewWeaponData)
{
	switch (NewWeaponData->GetHolsterType())
	{
	case EHolsterType::Primary:
		WeaponPrimaryHolster = WeaponInstance;
		break;
	case EHolsterType::Pistol:
		WeaponPistolHolster = WeaponInstance;
		break;
	default:
		break;
	}
}


// Called every frame
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
