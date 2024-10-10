// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/WeaponSystemComponent.h"

#include <iostream>

#include "NativeGameplayTags.h"
#include "Data/Weapon/WeaponData.h"
#include "Weapon/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "World/Weapons/MasterWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Componets/Bullets/CustomBulletProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/TimerHandle.h"
#include "Factories/BulletProjectileFactory.h"
#include "Player/PlayerCharacter.h"
#include "StateMachine/StateMachineComponent.h"

// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent(): CurrentWeaponInHands(nullptr), WeaponPistolHolster(nullptr),                                                 
                                                  WeaponTable(nullptr),
                                                  PlayerCamera(nullptr), SkeletalMeshComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UWeaponSystemComponent::bIsAnyWeaponInHands() const
{
	return CurrentWeaponInHands != nullptr;
}

void UWeaponSystemComponent::PostInitProperties()
{
	Super::PostInitProperties();

	ProjectileFactory = NewObject<UBulletProjectileFactory>();

	WeaponPrimaryHolster.SetNum(NumberOfWeaponPrimaryHolsters);

	auto Owner = Cast<APlayerCharacter>(GetOwner());
	if (Owner)
	{
		auto FindStateMachine_Aiming =  Cast<UStateMachineComponent>(Owner->GetDefaultSubobjectByName(TEXT("StateMachine_Aiming")));
		if (FindStateMachine_Aiming)
		{
			FindStateMachine_Aiming->StateChangedDelegate.AddDynamic(this, &UWeaponSystemComponent::SwitchStateMachine_Aiming);
		}		
	}
}

void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

	SwitchState(InitialStateTag);
}

bool UWeaponSystemComponent::bCheckHolsterAvaibility(EWeaponType BeingCheckedType, int NumberOfHolster) const
{
	switch (BeingCheckedType)
	{
	case EWeaponType::Primary:
		return WeaponPrimaryHolster[NumberOfHolster] == nullptr;

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

void UWeaponSystemComponent::InitializeFireSequence ()
{
	if (!CurrentWeaponInHands)
		return;
	
	EFireMode FireMode =CurrentWeaponInHands->GetSelectedFireMode();
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
	default:
		break;
	}
}

bool UWeaponSystemComponent::CheckIsCanShoot()
{
	//if (WeaponInteraction != EWeaponInteraction::None)
		//return false;
	
	if (!CurrentWeaponInHands
		|| CurrentStateTag == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.StartReload"))
		|| CurrentWeaponInHands->GetRoundsInMagazine()<=0)
		return false;
	
	if (GetWorld()->GetTimerManager().IsTimerActive(ShootDelayTimerHandle))
		return false;		
	
	if(bIsReadyToNextShoot && AvailableShootsCount>0)
	{			
		//UE_LOG(LogTemp, Warning, TEXT("Available Shoots Count: %d"), AvailableShootsCount);
		return true;
	}
	
	return false;
}

void UWeaponSystemComponent::TriggerFireWeapon () 
{
	if (!CurrentWeaponInHands)
		return;

	CurrentWeaponInHands->DecreaseRoundsInMagazine(); 

	switch (CurrentWeaponInHands->GetWeaponBaseRef()->GetEBulletMode())
	{
	case EBulletMode::HitScan:
		break;
	case EBulletMode::Projectile:
		ConfigureSpawnedProjectile ();
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

void UWeaponSystemComponent::ConfigureSpawnedProjectile ()
{
	if (!CurrentWeaponInHands->GetSkeletalMeshWeapon())
		return;

	const auto BulletSpawnPointTransform = CurrentWeaponInHands->GetSkeletalMeshWeapon()->GetSocketTransform(
		CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponAssetData().BulletSpawnSocketTransformName,
		ERelativeTransformSpace::RTS_World);
  
	if (BulletBlueprint)
	{
		if (!CurrentWeaponInHands->GetWeaponBaseRef()->GetSelectedAmmoData())
		{
			UE_LOG(LogTemp, Error, TEXT("Error: No usable ammo found"))
			return;
		}

		auto AmmoCharacteristics = CurrentWeaponInHands->GetWeaponBaseRef()->GetSelectedAmmoData()->GetAmmoCharacteristics();
		for (int i = 0; i < AmmoCharacteristics.NumberOfShotsPerRound; i++)
		{
			// Угол разброса
			auto SpreadAngle = CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().SpreadAngle;
			// Отклонение для разброса
			FRotator RandomSpread = FRotator(
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Pitch
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Yaw
				0.0f                                        // Roll (не нужно для разброса)
			);

			FVector SpawnLocation = BulletSpawnPointTransform.GetLocation();
			FRotator SpawnRotation = BulletSpawnPointTransform.GetRotation().Rotator() + AimOffset + RandomSpread;

			
			ServerProjectileSpawn(SpawnLocation, SpawnRotation, AmmoCharacteristics);
			if(OnShootDelegate.IsBound())
				OnShootDelegate.Broadcast(CurrentWeaponInHands->GetRoundsInMagazine());
		}
	}
}

void UWeaponSystemComponent::ServerProjectileSpawn_Implementation(const FVector& SpawnLocation,
	const FRotator& SpawnRotation, const FAmmoCharacteristics& AmmoCharacteristics)
{
	HandleProjectileSpawn(SpawnLocation, SpawnRotation, AmmoCharacteristics);
}

void UWeaponSystemComponent::HandleProjectileSpawn(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FAmmoCharacteristics& AmmoCharacteristics)
{
	if (!ProjectileFactory)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectileFactory is not valid."));
		return;
	}

	const FActorSpawnParameters SpawnParameters;
	auto NewBulletAmmoData = CurrentWeaponInHands->GetWeaponBaseRef()->GetSelectedAmmoData();
	auto NewAmmoCharacteristics = AmmoCharacteristics;
	NewBulletAmmoData->SetAmmoCharacteristics(NewAmmoCharacteristics);

	auto SpawnedActorRef = ProjectileFactory->CreateProjectile(GetWorld(), BulletBlueprint, SpawnLocation, SpawnRotation, SpawnParameters);
	if (SpawnedActorRef)
	{
		//ConfigureSpawnedProjectile(SpawnedActorRef, NewBulletAmmoData, AmmoCharacteristics);
		

		SpawnedActorRef->SetActorTickEnabled(false);
		SpawnedActorRef->SetActorHiddenInGame(true);

		if (const TObjectPtr<UCustomBulletProjectile> BulletProjectileComponent = SpawnedActorRef->FindComponentByClass<UCustomBulletProjectile>())
		{        				
			NewAmmoCharacteristics.StartBulletSpeed = CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().MuzzleVelocity;

			if (!CurrentWeaponInHands->GetWeaponBaseRef()->GetSelectedAmmoData())
			{
				UE_LOG(LogTemp, Error, TEXT("Error: Selected ammo data is null in %s"), *GetOwner()->GetName());
			}

			/*if(OnShootDelegate.IsBound())
				OnShootDelegate.Broadcast(CurrentWeaponInHands->GetRoundsInMagazine());*/

			BulletProjectileComponent->SetAmmoData(NewBulletAmmoData);
			BulletProjectileComponent->Init();
		}

		SpawnedActorRef->SetActorTickEnabled(true);
		SpawnedActorRef->SetActorHiddenInGame(false);
	}
}

bool UWeaponSystemComponent::SwitchState(FGameplayTag _StateTag)
{
	if (!_StateTag.MatchesTagExact(CurrentStateTag))
	{
		bCanTickState = false;
		
		ExitState();
		CurrentStateTag = _StateTag;
		InitState();

		bCanTickState= true;
		OnRep_CurrentStateTag();
		if(StateChangedDelegate.IsBound())
		{
			
			StateChangedDelegate.Broadcast(GetOwner(), CurrentStateTag);
		}
		return true;
	}
	else
	{
		if (bDebug)
		{
			
		}
	}

	return false;
}

void UWeaponSystemComponent::OnRep_CurrentStateTag()
{
	InitState();
	if (StateChangedDelegate.IsBound())
	{
		StateChangedDelegate.Broadcast(GetOwner(), CurrentStateTag);
	}
}

void UWeaponSystemComponent::InitStartingWeapon()
{
	if (!WeaponTable)
		return;

	//UE_LOG(LogTemp, Log, TEXT("WeaponSystemComponent Owner of %s is %s"), *GetName(), *GetOwner()->GetName());

	for (auto StartingWeapon : StartingWeapons)
	{
		if (StartingWeapon.IsNone())
			continue;

		const FWeaponData* WData = WeaponTable->FindRow<FWeaponData>(StartingWeapon, StartingWeapon.ToString());
		if (!WData)
		{
			UE_LOG(LogTemp, Error, TEXT("Not found %s"),* StartingWeapon.ToString());
			continue;
		}

		if (GetOwner() -> HasAuthority())
		//if (GetOwnerRole() == ROLE_AutonomousProxy)
		{
			//UE_LOG(LogTemp, Error, TEXT("SERVER. WeaponName %s"),* StartingWeapon.ToString());
			//
			//ServerAddWEA(StartingWeapon);
			//MulticastAddWEA(StartingWeapon, nullptr);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CLIENT. WeaponName %s"),* StartingWeapon.ToString());
			ServerAddWEA(StartingWeapon, GetOwner());
			
		}
	}
}

void UWeaponSystemComponent::AddWeapon(AMasterWeapon* Weapon, int NumberSlot)
{
	AssignWeaponToHolsterSlot(Weapon, NumberSlot);
	
}

void UWeaponSystemComponent::ServerAddWEA_Implementation(FName WeaponName, AActor* ActorFrom)
{
	MulticastAddWEA(WeaponName, ActorFrom);

	//
}

void UWeaponSystemComponent::MulticastAddWEA_Implementation(FName WeaponName, AActor* ActorFrom )
{
	const FWeaponData* WData = WeaponTable->FindRow<FWeaponData>(WeaponName, WeaponName.ToString());
	
	if (!WData)
		return;

	bool bIsFreeSlotFound = false;
	int NumberSlot = 0;
	if (WData->HolsterType == EWeaponType::Primary)
	{
		for(int i = 0; i < NumberOfWeaponPrimaryHolsters; i++)
		{
			if (bCheckHolsterAvaibility(WData->HolsterType, i) == true)
			{
				bIsFreeSlotFound = true;
				NumberSlot = i;
				break;
			}
		}
	}
	else if (WData->HolsterType ==EWeaponType::Pistol)
	{
		bIsFreeSlotFound = bCheckHolsterAvaibility (WData->HolsterType);
	}
		
	if (bIsFreeSlotFound == false)
		return;

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
			AmmoBase->SetAmmoCharacteristics(AData->AmmoCharacteristics);
								
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

	// Set up spawn parameters
	FActorSpawnParameters SpawnParameters;	
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Get the spawn location and transform
	const FVector SpawnLocation{GetOwner()->GetActorLocation()};
	const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);

	// Spawn the weapon with the new name
	AMasterWeapon* Weapon = GetWorld()->SpawnActor<AMasterWeapon>(AMasterWeapon::StaticClass(), SpawnTransform, SpawnParameters);
	
	Weapon->SetWeaponBaseRef(WeaponBase);
	Weapon->SwitchFireMode();
	Weapon->Reload();
	Weapon->UpdateVisual();
	Weapon->SetWeaponTableAndName(WeaponTable, WeaponBase->GetID());

	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
											   EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(SkeletalMeshComponent, AttachRule,
							  UWeaponHelper::ConvertHolsterTypeToText(WeaponBase->GetWeaponType()));

	// Append based on authority (Server or Client)
	/*if (GetOwner()->HasAuthority()) // Server
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER. WeaponName %s"),* WeaponName.ToString());
	}
	else // Client
	{
		//if (Weapon)
		//	AddWeapon(Weapon, NumberSlot);
		UE_LOG(LogTemp, Error, TEXT("CLIENT. WeaponName %s"),* WeaponName.ToString());
	}*/
	if (ActorFrom == this->GetOwner())
	{
		if (Weapon)
		AddWeapon(Weapon, NumberSlot);
		
	}
	
	
}

void UWeaponSystemComponent::AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, int NumberSlot)
{
	switch (WeaponInstance->GetWeaponBaseRef()->GetWeaponType())
	{
	case EWeaponType::Primary:
		WeaponPrimaryHolster[NumberSlot] = WeaponInstance;		
		break;
	case EWeaponType::Pistol:
		WeaponPistolHolster = WeaponInstance;
		break;
	default:
		break;
	}
}

bool UWeaponSystemComponent::CheckHolsterIsEmpty(EHolsterWeaponType Holster, int NumberOfHolster)
{
	switch (Holster)
	{
	case EHolsterWeaponType::None:
		return true;

	case EHolsterWeaponType::Pistol:
		if (!WeaponPistolHolster)
			return true;

	case EHolsterWeaponType::Primary:
		if (!WeaponPrimaryHolster[NumberOfHolster])

	case EHolsterWeaponType::AlternativePrimary:
		return true;
	}

	return false;
}

void UWeaponSystemComponent::TakeupArms(EHolsterWeaponType Holster, int NumberOfHolster)
{
	if (HandWeaponSocketName.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("HandWeaponSocketName is not set. Cannot attach weapon to socket."));
		return;
	}

	if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Skeleal MeshComponent is null. Cannot attach weapon to the skeletal mesh."));
		return;
	}

	if (LastUsedHolsterType != Holster && CurrentWeaponInHands)
	{
		//HideWeapon();
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
		if (!WeaponPrimaryHolster[NumberOfHolster] || WeaponPrimaryHolster[NumberOfHolster] == CurrentWeaponInHands)
			break;
		WeaponPrimaryHolster[NumberOfHolster]->AttachToComponent(SkeletalMeshComponent, AttachRule, HandWeaponSocketName);
		CurrentWeaponInHands = WeaponPrimaryHolster[NumberOfHolster];
		LastUsedHolsterType = Holster;
		break;

	case EHolsterWeaponType::AlternativePrimary:
		break;
	}

	BulletBlueprint = CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponAssetData().BulletActor;
	
	if (OnTakeupArmsDelegate.IsBound())
		OnTakeupArmsDelegate.Broadcast(CurrentWeaponInHands);
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

	if (OnHideArmsDelegate.IsBound())
		OnHideArmsDelegate.Broadcast();
}

bool UWeaponSystemComponent::IsCanStartReload()
{
	if (CurrentWeaponInHands == nullptr)
		return false;
	
	if (bIsAnyWeaponInHands() == false)
		return false;

	if (CurrentWeaponInHands->GetRoundsInMagazine() >= CurrentWeaponInHands->GetMagazineSize())
		return false;

	if (!CurrentStateTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.None"))))
		return false;
	
	return true;
}

void UWeaponSystemComponent::SwitchStateMachine_Aiming(AActor* Actor, const FGameplayTag& NewStateTag)
{
	static const FGameplayTag AimingTag = FGameplayTag::RequestGameplayTag(TEXT("PlayerAimingStates.Aiming"));	
	if (NewStateTag == AimingTag)
	{
		bIsNeedCalculateShootInfo = true;
	}
	else
	{
		bIsNeedCalculateShootInfo = false;
	}
}


void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateSocketsTransform();
}

void UWeaponSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		
	DOREPLIFETIME(UWeaponSystemComponent, CurrentStateTag);
	DOREPLIFETIME(UWeaponSystemComponent, CurrentWeaponInHands);
	DOREPLIFETIME(UWeaponSystemComponent, WeaponPrimaryHolster);
	
}

void UWeaponSystemComponent::InitState()
{
	if (InitStateDelegate.IsBound())
	{
		InitStateDelegate.Broadcast(CurrentStateTag);
	}

	if (CurrentStateTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.CompleteReload"))))
	{
		CurrentWeaponInHands->Reload();
		if (OnCompleteReloadDelegate.IsBound())
			OnCompleteReloadDelegate.Broadcast(CurrentWeaponInHands);
		
		SwitchState(FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.None")));
	}
}

void UWeaponSystemComponent::TickState(float DeltaTime) const
{
	if (TickStateDelegate.IsBound())
	{
		TickStateDelegate.Broadcast(DeltaTime, CurrentStateTag);
	}
}

void UWeaponSystemComponent::ExitState()
{
	if (StateHistory.Num()>= StateHistoryLenght)
	{
		StateHistory.RemoveAt(0);
	}
	StateHistory.Push(CurrentStateTag);
	
	if (ExitStateDelegate.IsBound())
	{
		ExitStateDelegate.Broadcast(CurrentStateTag);
	}

}
