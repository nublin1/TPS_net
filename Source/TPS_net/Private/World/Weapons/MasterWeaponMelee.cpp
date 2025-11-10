// Nublin Studio 2025 All Rights Reserved.


#include "World/Weapons/MasterWeaponMelee.h"

#include "Componets/Weapon/WeaponSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"


AMasterWeaponMelee::AMasterWeaponMelee()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMasterWeaponMelee::BeginPlay()
{
	Super::BeginPlay();

	if (StartingWeaponDataAsset)
	{
		InitWeaponBaseData(StartingWeaponDataAsset);
	}

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (APlayerCharacter* MyPawn = Cast<APlayerCharacter>(PC->GetPawn()))
		{
			if (WeaponOwnerActor == MyPawn)
			{
				bOwnerIsPlayer = true;
				PlayerCamera = MyPawn->GetCamera();
				SkeletalMeshCharacter = MyPawn->GetSkeletalMeshComponent();
				AnimInstanceCharacter = SkeletalMeshCharacter->GetAnimInstance();
			}
			else
			{
				bOwnerIsPlayer = false;
			}
			
		}
	}
}

void AMasterWeaponMelee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMasterWeaponMelee::InitWeaponBaseData(UWeaponDataAsset* NewWeaponDataAsset)
{
	Super::InitWeaponBaseData(NewWeaponDataAsset);

	if (HasAuthority())
	{
		WeaponDataAssetRef = NewWeaponDataAsset;
		
		UpdateVisual();
	}
}

void AMasterWeaponMelee::UpdateVisual()
{
	Super::UpdateVisual();

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

	if (WeaponDataAssetRef->WeaponAssetData.WeaponAnimationBlueprint)
		SkeletalMeshWeapon->SetAnimInstanceClass(
			WeaponDataAssetRef->WeaponAssetData.WeaponAnimationBlueprint->GetAnimBlueprintGeneratedClass());
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load animation class"));
	}
}

void AMasterWeaponMelee::SwitchAttackMode()
{
	
}

void AMasterWeaponMelee::InitializeAttackSequence()
{
	
}

void AMasterWeaponMelee::StopAttackSequence()
{
	
}

FAttackReadyResult AMasterWeaponMelee::CheckIsCanAttack()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(AttackDelayTimerHandle))
		return FAttackReadyResult(EAttackReadyStatus::AttackDelayActive, TEXT("Attack delay timer is active."));

	FString ReadyMessage = FString::Printf(TEXT("Weapon is ready"));
	return FAttackReadyResult(EAttackReadyStatus::Ready, ReadyMessage);
}

void AMasterWeaponMelee::AttackTrigger()
{
	OnFire();

	bIsReadyToNextAttack = false;

	GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandle, [this]()
	{
		bIsReadyToNextAttack = true;
	}, WeaponDataAssetRef->CharacteristicsOfTheWeaponMelee.AttackDelay, false);
}

void AMasterWeaponMelee::AimTrigger()
{
	
}
