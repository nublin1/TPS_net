// Nublin Studio 2025 All Rights Reserved.

#include "Componets/Weapon/WeaponSystemComponent.h"

#include "NativeGameplayTags.h"
#include "Data/Weapon/WeaponData.h"
#include "Engine/EngineTypes.h"
#include "World/Weapons/MasterWeaponRanged.h"
#include "Components/SkeletalMeshComponent.h"
#include "Componets/Weapon/WeaponSystemHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/PlayerCharacter.h"

#include "StateMachine/StateMachineComponent.h"


// Sets default values for this component's properties
UWeaponSystemComponent::UWeaponSystemComponent(): CurrentWeaponInHands(nullptr), WeaponPistolHolster(nullptr),                                                 
                                                   SkeletalMeshComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UWeaponSystemComponent::PostInitProperties()
{
	Super::PostInitProperties();

	WeaponPrimaryHolster.SetNum(NumberOfWeaponPrimaryHolsters);
	UnarmedHolster.SetNum(NumberOfWeaponUnarmedHolsters);

	auto Owner = Cast<APlayerCharacter>(GetOwner());
	if (Owner)
	{
		PlayerCharacterLink = Owner;
		
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
	DOREPLIFETIME(UWeaponSystemComponent, WeaponPistolHolster);
	DOREPLIFETIME(UWeaponSystemComponent, WeaponPrimaryHolster);
	DOREPLIFETIME(UWeaponSystemComponent, UnarmedHolster);
}

bool UWeaponSystemComponent::bIsAnyWeaponInHands() const
{
	return CurrentWeaponInHands != nullptr;
}

bool UWeaponSystemComponent::bCheckHolsterAvaibility(EHolsterWeaponType BeingCheckedType, int NumberOfHolster) const
{
	switch (BeingCheckedType)
	{
	case EHolsterWeaponType::Primary:
		return WeaponPrimaryHolster[NumberOfHolster] == nullptr;

	case EHolsterWeaponType::Pistol:
		return WeaponPistolHolster == nullptr;

	case EHolsterWeaponType::Unarmed:
		return UnarmedHolster[NumberOfHolster] == nullptr;
		
	default:
		return false;
	}
}

void UWeaponSystemComponent::UpdateSocketsTransform()
{
	if (CurrentWeaponInHands && SkeletalMeshComponent)
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

FAttackReadyResult UWeaponSystemComponent::CheckIsCanAttack()
{
	if (!CurrentWeaponInHands)
		return FAttackReadyResult(EAttackReadyStatus::WeaponNotEquipped, TEXT("Weapon is not equipped."));

	if (OwnerStateMachineComponent_Aiming)
	{
		if (CurrentStateTag == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.StartReload"))
			|| OwnerStateMachineComponent_Aiming->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.VelocityDirection")))
		{
			FString StateMessage = FString::Printf(TEXT("Weapon reload in progress or player not aiming. Current state: %s, Aiming state: %s"),
			*CurrentStateTag.ToString(),
			*OwnerStateMachineComponent_Aiming->GetCurrentStateTag().ToString());
			return FAttackReadyResult(EAttackReadyStatus::Unknown, StateMessage);
		}
	}
	

	if (PlayerCharacterLink && GetWorld()->GetTimerManager().IsTimerActive(
		PlayerCharacterLink->GetShootingPoseTransitionTimer()))
	{
		return FAttackReadyResult(EAttackReadyStatus::Unknown, TEXT("Anim state transition in progress"));
	}
	
	return CurrentWeaponInHands->CheckIsCanAttack();
	
	//return FAttackReadyResult(EAttackReadyStatus::Unknown, TEXT("Unknown shoot readiness state."));
}

void UWeaponSystemComponent::TriggerAttack() 
{
	if (!CurrentWeaponInHands)
		return;

	CurrentWeaponInHands->InitializeAttackSequence();
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
	if (StartingWeaponsArray.IsEmpty())
		return;

	for (auto StartingWeapon : StartingWeaponsArray)
	{
		if (!StartingWeapon)
			continue;

		UWeaponDataAsset* TempWeaponDataAsset = StartingWeapon;
				
		//UE_LOG(LogTemp, Error, TEXT("CLIENT. WeaponName %s"),* StartingWeapon.ToString());
		ServerAddWeapon(StartingWeapon);
	}
}

void UWeaponSystemComponent::AddWeapon(AMasterWeaponRanged* Weapon, int NumberSlot)
{
	AssignWeaponToHolsterSlot(Weapon, NumberSlot);
}

void UWeaponSystemComponent::ServerAddWeapon_Implementation(UWeaponDataAsset* WeaponData)
{
	if (!WeaponData)
		return;

	bool bIsFreeSlotFound = false;
	int NumberSlot = 0;
	if (WeaponData->HolsterWeaponType == EHolsterWeaponType::Primary)
	{
		for(int i = 0; i < NumberOfWeaponPrimaryHolsters; i++)
		{
			if (bCheckHolsterAvaibility(WeaponData->HolsterWeaponType, i) == true)
			{
				bIsFreeSlotFound = true;
				NumberSlot = i;
				break;
			}
		}
	}
	else if (WeaponData->HolsterWeaponType ==EHolsterWeaponType::Pistol)
	{
		bIsFreeSlotFound = bCheckHolsterAvaibility (WeaponData->HolsterWeaponType);
	}
	else if (WeaponData->HolsterWeaponType == EHolsterWeaponType::Unarmed)
	{
		for(int i = 0; i < NumberOfWeaponUnarmedHolsters; i++)
		{
			if (bCheckHolsterAvaibility(WeaponData->HolsterWeaponType, i) == true)
			{
				bIsFreeSlotFound = true;
				NumberSlot = i;
				break;
			}
		}
	}
		
	if (bIsFreeSlotFound == false)
		return;
	

	// Set up spawn parameters
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Get the spawn location and transform
	const FVector SpawnLocation{GetOwner()->GetActorLocation()};
	const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);

	if (WeaponData->WeaponType == EWeaponType::Melee)
	{
		
	}
	else
	{
		// Spawn the weapon
		if (!WeaponClassRanged)
		{
			UE_LOG(LogTemp, Warning, TEXT("WeaponClass is null"));
			return;
		}

		auto Weapon = GetWorld()->SpawnActorDeferred<AMasterWeaponRanged>(WeaponClassRanged, SpawnTransform, GetOwner(),
			nullptr, SpawnParameters.SpawnCollisionHandlingOverride);
		if (!Weapon)
		{
			return;
		}
		Weapon->SetOwner(GetOwner());
		Weapon->SetWeaponOwnerActor(GetOwner());
		Weapon->SetReplicates(true);

		UGameplayStatics::FinishSpawningActor(Weapon, SpawnTransform);
		Weapon->SetWeaponBaseRef(WeaponData);
		Weapon->SwitchFireMode();
		Weapon-> StartReload();
		Weapon->UpdateVisual();

		const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
												   EAttachmentRule::SnapToTarget, true);
		Weapon->AttachToComponent(SkeletalMeshComponent, AttachRule,
								  UWeaponHelper::ConvertHolsterTypeToText(WeaponData->HolsterWeaponType));
		
		AddWeapon(Weapon, NumberSlot);
	}
}

void UWeaponSystemComponent::AssignWeaponToHolsterSlot(ABaseWeapon* WeaponInstance, int NumberSlot)
{
	switch (WeaponInstance->GetWeaponDataAssetRef()->HolsterWeaponType)
	{
	case EHolsterWeaponType::Primary:
		WeaponPrimaryHolster[NumberSlot] = WeaponInstance;
		break;
	case EHolsterWeaponType::Pistol:
		WeaponPistolHolster = WeaponInstance;
		break;
	case EHolsterWeaponType::Unarmed:
		UnarmedHolster[NumberSlot] = WeaponInstance;
	default:
		break;
	}

	if (AutoEquipLast)
		TakeupArms(WeaponInstance->GetWeaponDataAssetRef()->HolsterWeaponType, NumberSlot);
	
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
		break;

	case EHolsterWeaponType::Primary:
		if (!WeaponPrimaryHolster[NumberOfHolster])
			return true;
		break;

	case EHolsterWeaponType::AlternativePrimary:
		return true;
		
	case EHolsterWeaponType::Unarmed:
		if (!UnarmedHolster[NumberOfHolster])
			return true;
		break;
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

	/*if (!SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Skeletal MeshComponent is null. Cannot attach weapon to the skeletal mesh."));
		return;
	}*/

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
	case EHolsterWeaponType::Unarmed:
		if (!UnarmedHolster[NumberOfHolster] || UnarmedHolster[NumberOfHolster] == CurrentWeaponInHands)
			break;
		CurrentWeaponInHands = UnarmedHolster[NumberOfHolster];
		LastUsedHolsterType = Holster;
		break;
	}
	
	OnRep_CurrentWeaponInHands();
}

void UWeaponSystemComponent::HideWeapon()
{
	if (!CurrentWeaponInHands)
		return;

	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	                                           EAttachmentRule::SnapToTarget, true);

	CurrentWeaponInHands->AttachToComponent(SkeletalMeshComponent, AttachRule,
		                                        CurrentWeaponInHands->GetWeaponDataAssetRef()->HolsterName);
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

	if (CurrentWeaponInHands->GetWeaponDataAssetRef()->bReloadingByCooldown)
		return false;
		
	if (!CurrentStateTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.None"))))
		return false;

	auto IsCan = CurrentWeaponInHands->IsCanStartReload();
	
	return IsCan;
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

void UWeaponSystemComponent::InitState()
{
	if (InitStateDelegate.IsBound())
	{
		InitStateDelegate.Broadcast(CurrentStateTag);
	}

	if (CurrentStateTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.CompleteReload"))))
	{
		CurrentWeaponInHands->StartReload();		
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
