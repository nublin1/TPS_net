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
		AvailableShootsCount = 3;
		break;
	case EFireMode::Full_Auto:
		AvailableShootsCount = CurrentWeaponInHands->GetRoundsInMagazine();
		break;
	}
}

bool UWeaponSystemComponent::CheckIsCanShoot()
{
	if (WeaponInteraction != EWeaponInteraction::None)
		return false;
	
	if (!CurrentWeaponInHands)
		return false;
	
	if (GetWorld()->GetTimerManager().IsTimerActive(ShootDelayTimerHandle))
		return false;
	
	if(CurrentWeaponInHands->GetRoundsInMagazine()<=0)
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
	CurrentWeaponInHands->DecreaseRoundsInMagazine(); 
	bIsReadyToNextShoot = false;
	
	GetWorld()->GetTimerManager().SetTimer(ShootDelayTimerHandle, [this]()
	{
		bIsReadyToNextShoot = true;
	},  60.0f / CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().RPM , false);
	
	
}

void UWeaponSystemComponent::ShootProjectile() const
{
	if (!CurrentWeaponInHands->GetSkeletalMeshWeapon())
		return;

	auto BulletSpawnPointTransform = CurrentWeaponInHands->GetSkeletalMeshWeapon()->GetSocketTransform(
		CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponAssetData().BulletSpawnSocketTransformName,
		ERelativeTransformSpace::RTS_World);
	UBlueprint* BulletBlueprint = CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponAssetData().BulletActor;
	if (BulletBlueprint)
	{
		FActorSpawnParameters SpawnParameters;
		FVector SpawnLocation = BulletSpawnPointTransform.GetLocation();
		FRotator SpawnRotation = BulletSpawnPointTransform.GetRotation().Rotator();

		for (int i =0; i<CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().NumberOfShotsPerRound; i++)
		{
			// Угол разброса
			auto SpreadAngle = CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().SpreadAngle;
			// Отклонение для разброса
			FRotator RandomSpread = FRotator(
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Pitch
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Yaw
				0.0f                                        //Roll (не нужно для разброса)
			);
		
			SpawnRotation += RandomSpread;

			AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(BulletBlueprint->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParameters);
			if (SpawnedActorRef)
			{
				UCustomBulletProjectile* BulletProjectileComponent = SpawnedActorRef->FindComponentByClass<UCustomBulletProjectile>();
				if (BulletProjectileComponent)
				{			
					BulletProjectileComponent->SetStartBulletSpeed(10.0f);

					if (!CurrentWeaponInHands->GetWeaponBaseRef()->GetSelectedAmmoData())
					{
						UE_LOG(LogTemp, Error, TEXT("Error: Selected ammo data is null in %s"), *GetOwner()->GetName());
						BulletProjectileComponent->SetBulletMass(1);
					}
					else
					{
						BulletProjectileComponent->SetBulletMass(CurrentWeaponInHands->GetWeaponBaseRef()->GetSelectedAmmoData()->GetAmmoCharacteristics().BulletMass);
					}					
				}
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
		WeaponBase->SetCharacteristicsOfTheWeapon(WData->CharacteristicsOfTheWeapon);
		WeaponBase->SetWeaponAssetData(WData->WeaponAssetData);
		WeaponBase->SetWeaponType(WData->HolsterType);

		if(!WData->CharacteristicsOfTheWeapon.UsableAmmo.IsEmpty())
		{
			TArray<UAmmoBase*> tempAmmo;
			for (auto Element : WData->CharacteristicsOfTheWeapon.UsableAmmo)
			{		
				const FAmmoData* AData = Element.DataTable->FindRow<FAmmoData>(Element.RowName, Element.RowName.ToString());
				if (!AData)
					continue;

				UAmmoBase* AmmoBase = NewObject<UAmmoBase>(this, UAmmoBase::StaticClass());
								
				tempAmmo.Add(AmmoBase);
			}
			if (tempAmmo.Num() > 0)
			{
				WeaponBase->SetSelectedAmmoData(tempAmmo[0]);
				WeaponBase->SetUsableAmmo(tempAmmo);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Error: No usable ammo found after processing."));
			}
		}

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
