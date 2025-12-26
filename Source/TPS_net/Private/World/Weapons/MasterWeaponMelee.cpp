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
			if (WeaponOwnerActor && WeaponOwnerActor == MyPawn)
			{
				bOwnerIsPlayer = true;
				OwnerCamera = MyPawn->GetCamera();
				SkeletalMeshCharacter = MyPawn->GetSkeletalMeshComponent();
				AnimInstanceCharacter = SkeletalMeshCharacter->GetAnimInstance();
			}
			else if (WeaponOwnerActor)
			{
				bOwnerIsPlayer = false;
				if (auto OwnerSkeletalMesh = WeaponOwnerActor->FindComponentByClass<USkeletalMeshComponent>())
					SkeletalMeshCharacter = OwnerSkeletalMesh;
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

	UpdateTracePoints();
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

void AMasterWeaponMelee::AttackTrigger(TSubclassOf<UGameplayAbility> AbilityClass)
{
	CurrentAttackAbilityClass = AbilityClass;
	if (const FWeaponAbilityData* FoundData = WeaponDataAssetRef->GrantedAbilities.Find(CurrentAttackAbilityClass))
		CurrentAbilityData = *FoundData;
	
	
	OnFire();
	bIsReadyToNextAttack = false;

	GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandle, [this]()
	{
		bIsReadyToNextAttack = true;
	}, WeaponDataAssetRef->WeaponMeleeAttackData.AttackDelay, false);
}

void AMasterWeaponMelee::AimTrigger()
{
	
}
