// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/WeaponSystemComponent.h"

#include "NativeGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Data/Weapon/WeaponData.h"
#include "Weapon/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "World/Weapons/MasterWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Componets/Bullets/CustomBulletProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Factories/BulletProjectileFactory.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/PlayerCharacter.h"

#include "StateMachine/StateMachineComponent.h"

// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent(): CurrentWeaponInHands(nullptr), WeaponPistolHolster(nullptr),                                                 
                                                  WeaponTable(nullptr),
                                                  PlayerCamera(nullptr), SkeletalMeshComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
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
		auto ResultStateMachine_Aiming =  Cast<UStateMachineComponent>(Owner->GetDefaultSubobjectByName(TEXT("StateMachine_Aiming")));
		if (ResultStateMachine_Aiming)
		{
			OwnerStateMachineComponent_Aiming = ResultStateMachine_Aiming;
			OwnerStateMachineComponent_Aiming->StateChangedDelegate.AddDynamic(this, &UWeaponSystemComponent::SwitchStateMachine_Aiming);
			OwnerStateMachineComponent_Aiming->InitStateDelegate.AddDynamic(this, &UWeaponSystemComponent::InitState_Aiming);
		}		
	}
}

void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

	SwitchState(InitialStateTag);
}

bool UWeaponSystemComponent:: bCheckHolsterAvaibility(EHolsterWeaponType BeingCheckedType, int NumberOfHolster) const
{
	switch (BeingCheckedType)
	{
	case EHolsterWeaponType::Primary:
		return WeaponPrimaryHolster[NumberOfHolster] == nullptr;

	case EHolsterWeaponType::Pistol:
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

void UWeaponSystemComponent::StopFireSequence()
{
	bIsStartShooting = false;
	OnStopFireDelegate.Broadcast();
	if (CurrentWeaponInHands)
		CurrentWeaponInHands->OnStopFire();
}

void UWeaponSystemComponent::InitializeFireSequence ()
{
	if (!CurrentWeaponInHands)
		return;

	switch (EFireMode FireMode = CurrentWeaponInHands->GetSelectedFireMode())
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

FShootReadyResult UWeaponSystemComponent::CheckIsCanShoot()
{
	if (!CurrentWeaponInHands)
		return FShootReadyResult(EShootReadyStatus::WeaponNotEquipped, TEXT("Weapon is not equipped."));

	if (CurrentWeaponInHands->GetRoundsInMagazine()<=0)
		return FShootReadyResult(EShootReadyStatus::NoAmmo, TEXT("No ammo left."));
	
	if (!CurrentWeaponInHands
		|| CurrentStateTag == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.StartReload"))
		|| OwnerStateMachineComponent_Aiming->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.NoAiming")))
		return FShootReadyResult(EShootReadyStatus::Unknown);
	
	if (GetWorld()->GetTimerManager().IsTimerActive(ShootDelayTimerHandle))
		return FShootReadyResult(EShootReadyStatus::ShootDelayActive);	
	
	if(bIsReadyToNextShoot && AvailableShootsCount>0)
	{
		//FString Message = FString::Printf(TEXT("Available Shoots Count: %d"), AvailableShootsCount);
		//UKismetSystemLibrary::PrintString(this, Message, true, false, FLinearColor::Yellow, 5.0f);
		
		OnStartFireSignatureDelegate.Broadcast();
		if (!bIsStartShooting)
		{
			bIsStartShooting = true;
			CurrentWeaponInHands->OnStartFire();
		}
		
		return FShootReadyResult(EShootReadyStatus::Ready);
	}
	
	return FShootReadyResult(EShootReadyStatus::Unknown);
}

void UWeaponSystemComponent::TriggerFireWeapon() 
{
	if (!CurrentWeaponInHands)
		return;

	
	CurrentWeaponInHands->OnFire();
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

	BulletBlueprint =  CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponAssetData().BulletActor;
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
			// Spreading angle
			auto SpreadAngle = CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().SpreadAngle;
			// Отклонение для разброса
			FRotator RandomSpread = FRotator(
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Pitch
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Yaw
				0.0f                                        // Roll (не нужно для разброса)
			);

			FVector SpawnLocation = PlayerCamera->K2_GetComponentLocation();
			FRotator SpawnRotation = PlayerCamera->GetComponentRotation() + RandomSpread;

			//FVector SpawnLocation = BulletSpawnPointTransform.GetLocation();
			//FRotator SpawnRotation = BulletSpawnPointTransform.GetRotation().Rotator() + AimOffset + RandomSpread;
			//FRotator SpawnRotation = BulletSpawnPointTransform.GetRotation().Rotator() + RandomSpread;
			
			ServerProjectileSpawn(SpawnLocation, SpawnRotation, AmmoCharacteristics, CurrentWeaponInHands);
			if(OnSpawnedProjectile.IsBound())
				OnSpawnedProjectile.Broadcast(CurrentWeaponInHands->GetRoundsInMagazine());
		}
	}
}

void UWeaponSystemComponent::ServerProjectileSpawn_Implementation(const FVector& SpawnLocation,
	const FRotator& SpawnRotation, const FAmmoCharacteristics& AmmoCharacteristics, AActor* Owner)
{
	HandleProjectileSpawn(SpawnLocation, SpawnRotation, AmmoCharacteristics, Owner);
}

void UWeaponSystemComponent::HandleProjectileSpawn(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FAmmoCharacteristics& AmmoCharacteristics, AActor* Owner)
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
		SpawnedActorRef->SetOwner(Owner);

		//UE_LOG(LogTemp, Error, TEXT("Error: Owner of SpawnedActorRef is %s"), *Owner->GetName());

		if (const TObjectPtr<UCustomBulletProjectile> BulletProjectileComponent = SpawnedActorRef->FindComponentByClass<UCustomBulletProjectile>())
		{        				
			NewAmmoCharacteristics.StartBulletSpeed = CurrentWeaponInHands->GetWeaponBaseRef()->GetCharacteristicsOfTheWeapon().MuzzleVelocity;

			if (!CurrentWeaponInHands->GetWeaponBaseRef()->GetSelectedAmmoData())
			{
				UE_LOG(LogTemp, Error, TEXT("Error: Selected ammo data is null in %s"), *GetOwner()->GetName());
			}

			BulletProjectileComponent->SetAmmoData(NewBulletAmmoData);
			BulletProjectileComponent->Init();
		}

		SpawnedActorRef->SetActorTickEnabled(true);
		SpawnedActorRef->SetActorHiddenInGame(false);
	}
}

bool UWeaponSystemComponent::IsCanHideWeapon()
{
	if (CurrentStateTag == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Hide"))
		|| CurrentStateTag == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Takeup")))
		return false;
	
	if (!CurrentWeaponInHands)
		return false;

	return true;
}

void UWeaponSystemComponent::SwitchState_Implementation(FGameplayTag _NewStateTag)
{
	if (!_NewStateTag.MatchesTagExact(CurrentStateTag))
	{
		bCanTickState = false;
		
		ExitState();
		CurrentStateTag = _NewStateTag;
		InitState();

		bCanTickState= true;
		OnRep_CurrentStateTag();
		if(OnStateChangedDelegate.IsBound())
		{
			OnStateChangedDelegate.Broadcast(GetOwner(), _NewStateTag);
		}
	}
	else
	{
		if (bDebug)
		{
			
		}
	}
}

void UWeaponSystemComponent::OnRep_CurrentStateTag()
{
	InitState();
	if (OnStateChangedDelegate.IsBound())
	{
		OnStateChangedDelegate.Broadcast(GetOwner(), CurrentStateTag);
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
				
		//UE_LOG(LogTemp, Error, TEXT("CLIENT. WeaponName %s"),* StartingWeapon.ToString());
		ServerAddWEA(StartingWeapon, GetOwner());
	}
}

void UWeaponSystemComponent::AddWeapon(AMasterWeapon* Weapon, int NumberSlot)
{
	AssignWeaponToHolsterSlot(Weapon, NumberSlot);
}

void UWeaponSystemComponent::ServerAddWEA_Implementation(FName WeaponName, AActor* ActorFrom)
{
	const FWeaponData* WData = WeaponTable->FindRow<FWeaponData>(WeaponName, WeaponName.ToString());
	
	if (!WData)
		return;

	bool bIsFreeSlotFound = false;
	int NumberSlot = 0;
	if (WData->HolsterWeaponType == EHolsterWeaponType::Primary)
	{
		for(int i = 0; i < NumberOfWeaponPrimaryHolsters; i++)
		{
			if (bCheckHolsterAvaibility(WData->HolsterWeaponType, i) == true)
			{
				bIsFreeSlotFound = true;
				NumberSlot = i;
				break;
			}
		}
	}
	else if (WData->HolsterWeaponType ==EHolsterWeaponType::Pistol)
	{
		bIsFreeSlotFound = bCheckHolsterAvaibility (WData->HolsterWeaponType);
	}
		
	if (bIsFreeSlotFound == false)
		return;

	TObjectPtr<UWeaponBase> WeaponBase = NewObject<UWeaponBase>(this, UWeaponBase::StaticClass());
	WeaponBase->SetID(WData->Name);
	WeaponBase->SetWeaponType(WData->WeaponType);
	WeaponBase->SetWeaponGripType(WData->WeaponGripType);
	WeaponBase->SetHolsterWeaponType(WData->HolsterWeaponType);
	WeaponBase->SetBulletMode(WData->BulletMode);
	WeaponBase->SetCharacteristicsOfTheWeapon(WData->CharacteristicsOfTheWeapon);
	WeaponBase->SetWeaponAssetData(WData->WeaponAssetData);
	

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
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Get the spawn location and transform
	const FVector SpawnLocation{GetOwner()->GetActorLocation()};
	const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);

	// Spawn the weapon
	if (!WeaponClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponClass is null"));
		return;
	}
	
	auto Weapon = GetWorld()->SpawnActor<AMasterWeapon>(WeaponClass, SpawnTransform, SpawnParameters);
	if (!Weapon)
	{
		return;
	}
	Weapon->SetOwner(GetOwner());
	Weapon->SetReplicates(true);
	Weapon->SetWeaponBaseRef(WeaponBase);
	Weapon->SwitchFireMode();
	Weapon->Reload();
	Weapon->UpdateVisual();
	Weapon->SetWeaponTableAndName(WeaponTable, WeaponBase->GetID());

	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
											   EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(SkeletalMeshComponent, AttachRule,
							  UWeaponHelper::ConvertHolsterTypeToText(WeaponBase->GetHolsterWeaponType()));

	
	//if (ActorFrom == this->GetOwner())
	{
		if (Weapon)
		AddWeapon(Weapon, NumberSlot);
		
	}
}

void UWeaponSystemComponent::AssignWeaponToHolsterSlot(AMasterWeapon* WeaponInstance, int NumberSlot)
{
	switch (WeaponInstance->GetWeaponBaseRef()->GetHolsterWeaponType())
	{
	case EHolsterWeaponType::Primary:
		WeaponPrimaryHolster[NumberSlot] = WeaponInstance;		
		break;
	case EHolsterWeaponType::Pistol:
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
		UE_LOG(LogTemp, Error, TEXT("Skeletal MeshComponent is null. Cannot attach weapon to the skeletal mesh."));
		return;
	}

	if (LastUsedHolsterType != Holster && CurrentWeaponInHands)
	{
		//HideWeapon();
	}

	switch (Holster)
	{
	case EHolsterWeaponType::None:
		break;

	case EHolsterWeaponType::Pistol:
		if (!WeaponPistolHolster || WeaponPistolHolster == CurrentWeaponInHands)
			break;
		
		CurrentWeaponInHands = WeaponPistolHolster;
		LastUsedHolsterType = Holster;
		break;

	case EHolsterWeaponType::Primary:
		if (!WeaponPrimaryHolster[NumberOfHolster] || WeaponPrimaryHolster[NumberOfHolster] == CurrentWeaponInHands)
			break;
		CurrentWeaponInHands = WeaponPrimaryHolster[NumberOfHolster];
		LastUsedHolsterType = Holster;
		break;

	case EHolsterWeaponType::AlternativePrimary:
		break;
	}

	auto result = CurrentWeaponInHands->GetWeaponBaseRef()->GetWeaponAssetData().BulletActor;
	BulletBlueprint = result;
	
	OnRep_CurrentWeaponInHands();
}

void UWeaponSystemComponent::HideWeapon()
{
	if (!CurrentWeaponInHands)
		return;

	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                           EAttachmentRule::SnapToTarget, true);

	CurrentWeaponInHands->AttachToComponent(SkeletalMeshComponent, AttachRule,
	                                        UWeaponHelper::ConvertHolsterTypeToText(
		                                        CurrentWeaponInHands->GetWeaponBaseRef()->GetHolsterWeaponType()));
	if (OnHideArmsDelegate.IsBound())
		OnHideArmsDelegate.Broadcast(CurrentWeaponInHands);
	
	CurrentWeaponInHands = nullptr;

	
}

void UWeaponSystemComponent::AttachWeapon(AActor* ActorToAttach, FName SocketName)
{
	if (!ActorToAttach)
		return;
	
	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
											   EAttachmentRule::SnapToTarget, true);

	ActorToAttach->AttachToComponent(SkeletalMeshComponent, AttachRule, SocketName);
}

void UWeaponSystemComponent::OnRep_CurrentWeaponInHands()
{
	if (CurrentWeaponInHands)
		AttachWeapon(CurrentWeaponInHands, HandWeaponSocketName);

	if (OnTakeupArmsDelegate.IsBound())
		OnTakeupArmsDelegate.Broadcast(CurrentWeaponInHands);
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
	static const FGameplayTag HipAimingTag = FGameplayTag::RequestGameplayTag(TEXT("PlayerAimingStates.HipAiming"));
	if (NewStateTag == AimingTag || NewStateTag == HipAimingTag)
	{
		bIsNeedCalculateShootInfo = true;
	}
	else
	{
		bIsNeedCalculateShootInfo = false;
	}
}

void UWeaponSystemComponent::InitState_Aiming(const FGameplayTag& NewStateTag)
{
	static const FGameplayTag AimingTag = FGameplayTag::RequestGameplayTag(TEXT("PlayerAimingStates.HipAiming"));
	if (NewStateTag == AimingTag)
	{
		
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

	DOREPLIFETIME(UWeaponSystemComponent, bIsStartShooting);	
	DOREPLIFETIME(UWeaponSystemComponent, CurrentStateTag);
	DOREPLIFETIME(UWeaponSystemComponent, CurrentWeaponInHands);
	DOREPLIFETIME(UWeaponSystemComponent, WeaponPistolHolster);
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
