// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/WeaponSystemComponent.h"

#include <iostream>

#include "Data/Weapon/WeaponData.h"
#include "Weapon/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "World/Weapons/MasterWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Componets/Bullets/CustomBulletProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/TimerHandle.h"

// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent(): CurrentWeaponInHands(nullptr), WeaponPistolHolster(nullptr),
                                                  WeaponPrimaryHolster(nullptr),
                                                  WeaponTable(nullptr), SkeletalMeshComponent(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

bool UWeaponSystemComponent::bIsAnyWeaponInHands() const
{
	return CurrentWeaponInHands != nullptr;
}

void UWeaponSystemComponent::PostInitProperties()
{
	Super::PostInitProperties();
}

// Called when the game startsKO
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

bool UWeaponSystemComponent::bCheckHolsterAvaibility(EWeaponType BeingCheckedType) const
{
	switch (BeingCheckedType)
	{
	case EWeaponType::Primary:
		return WeaponPrimaryHolster == nullptr;

	case EWeaponType::Pistol:
		return WeaponPistolHolster == nullptr;

	default:
		return false;
	}
}

void UWeaponSystemComponent::UpdateSocketsTransform()
{
	if (CurrentWeaponInHands)
	{
		//LeftHandSocketTransform = CurrentWeaponInHands->GetSkeletalMeshWeapon()->GetSocketTransform(LeftHandSocketName, RTS_World);
		auto lhand = CurrentWeaponInHands->GetSkeletalMeshWeapon()->GetSocketTransform(LeftHandSocketName, RTS_World);
		auto rhand = SkeletalMeshComponent->GetSocketTransform("hand_r", RTS_World);
		LeftHandSocketTransform = UKismetMathLibrary::MakeRelativeTransform(lhand, rhand);
	}
	else
	{
		LeftHandSocketTransform = FTransform::Identity;
	}
}

void UWeaponSystemComponent::PreShoot()
{
	if (!CurrentWeaponInHands)
		return;
	
	EFireMode FireMode = EFireMode::Single;
	switch (FireMode)
	{
	case EFireMode::Single:
		AvailableShootsCount = 1;
		break;
	case EFireMode::Burst:
		break;
	case EFireMode::Full_Auto:
		break;
	}
}

bool UWeaponSystemComponent::CheckIsCanShoot()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ShootDelayTimerHandle))
		return false;
	
	if(bIsReadyToNextShoot && AvailableShootsCount>0)
	{			
		//UE_LOG(LogTemp, Warning, TEXT("Available Shoots Count: %d"), AvailableShootsCount);

		return true;
	}
	
	return false;
}

void UWeaponSystemComponent::Shoot() 
{
	if (!CurrentWeaponInHands)
		return;

	if (CheckIsCanShoot() == false)
		return;

	switch (CurrentWeaponInHands->GetWeaponBaseRef()->GetEBulletMode())
	{
	case EBulletMode::HitScan:
		break;
	case EBulletMode::Projectile:
		ShootProjectile();
		break;
	default:
		break;
	}

	AvailableShootsCount--;
	bIsReadyToNextShoot = false;
	
	GetWorld()->GetTimerManager().SetTimer(ShootDelayTimerHandle, [this]()
	{
		bIsReadyToNextShoot = true;
	},  60.0f / CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().RPM , false);
	
	
}

void UWeaponSystemComponent::ShootProjectile() const
{
	auto BulletSpawnPointTransform = CurrentWeaponInHands->GetSkeletalMeshWeapon()->GetSocketTransform(
		"MuzzleFlash", RTS_World);
	auto actorToSpawn = CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponAssetData().BulletActor;
	FActorSpawnParameters SpawnParameters;
	if (actorToSpawn)
	{
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(actorToSpawn->GeneratedClass,
																 BulletSpawnPointTransform.GetLocation(),
																 BulletSpawnPointTransform.GetRotation().Rotator(),
																 SpawnParameters);
		if (SpawnedActorRef)
		{
			UCustomBulletProjectile* BulletProjectileComponent = SpawnedActorRef->FindComponentByClass<UCustomBulletProjectile>();
			if (BulletProjectileComponent)
			{
				// Настройте необходимые переменные компонента здесь
				BulletProjectileComponent->SetStartBulletSpeed(10.0f);
				BulletProjectileComponent->SetBulletMass(CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().Mass);
				
			}
		}
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
		WeaponBase->SetBulletMode(WData->BulletMode);
		WeaponBase->SetWeaponAssetData(WData->WeaponAssetData);
		WeaponBase->SetWeaponType(WData->HolsterType);

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

	const FVector SpawnLocation{GetOwner()->GetActorLocation()};
	const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);
	AMasterWeapon* Weapon = GetWorld()->SpawnActor<AMasterWeapon>(AMasterWeapon::StaticClass(), SpawnTransform,
	                                                              SpawnParameters);
	Weapon->SetWeaponBaseRef(NewWeaponData);
	Weapon->UpdateVisual();

	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                           EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(SkeletalMeshComponent, AttachRule,
	                          UWeaponHelper::ConvertHolsterTypeToText(NewWeaponData->GetWeaponType()));

	AssignWeaponToHolsterSlot(Weapon, NewWeaponData);
}

void UWeaponSystemComponent::AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, UWeaponBase* NewWeaponData)
{
	switch (NewWeaponData->GetWeaponType())
	{
	case EWeaponType::Primary:
		WeaponPrimaryHolster = WeaponInstance;
		break;
	case EWeaponType::Pistol:
		WeaponPistolHolster = WeaponInstance;
		break;
	default:
		break;
	}
}

void UWeaponSystemComponent::TakeupArms(EHolsterWeaponType Holster)
{
	if (HandWeaponSocketName.IsNone())
		return;

	if (!SkeletalMeshComponent)
		return;

	if (LastUsedHolsterType != Holster && CurrentWeaponInHands)
	{
		HideWeapon();
	}

	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                           EAttachmentRule::SnapToTarget, true);

	switch (Holster)
	{
	case EHolsterWeaponType::None:
		break;

	case EHolsterWeaponType::Pistol:
		if (!WeaponPistolHolster || WeaponPistolHolster == CurrentWeaponInHands)
			break;
		WeaponPistolHolster->AttachToComponent(SkeletalMeshComponent, AttachRule, HandWeaponSocketName);
		CurrentWeaponInHands = WeaponPistolHolster;
		LastUsedHolsterType = Holster;
		break;

	case EHolsterWeaponType::Primary:
		if (!WeaponPrimaryHolster || WeaponPrimaryHolster == CurrentWeaponInHands)
			break;
		WeaponPrimaryHolster->AttachToComponent(SkeletalMeshComponent, AttachRule, HandWeaponSocketName);
		CurrentWeaponInHands = WeaponPrimaryHolster;
		LastUsedHolsterType = Holster;
		break;

	case EHolsterWeaponType::AlternativePrimary:
		break;
	}
}

void UWeaponSystemComponent::HideWeapon()
{
	if (!CurrentWeaponInHands)
		return;

	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                           EAttachmentRule::SnapToTarget, true);

	CurrentWeaponInHands->AttachToComponent(SkeletalMeshComponent, AttachRule,
	                                        UWeaponHelper::ConvertHolsterTypeToText(
		                                        CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponType()));
	CurrentWeaponInHands = nullptr;
}


// Called every frame
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateSocketsTransform();
}

void UWeaponSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);

	TArray<FLifetimeProperty> OutLifetimeProps;

	DOREPLIFETIME(UWeaponSystemComponent, WeaponInteraction);
}
