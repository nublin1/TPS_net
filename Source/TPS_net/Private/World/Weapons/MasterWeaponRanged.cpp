// Nublin Studio 2025 All Rights Reserved.

#include "World/Weapons/MasterWeaponRanged.h"

#include "Camera/CameraComponent.h"
#include "Componets/Bullets/CustomBulletProjectile.h"
#include "Factories/BulletProjectileFactory.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/PlayerCharacter.h"


AMasterWeaponRanged::AMasterWeaponRanged(): CurrentRecoilTime(0)
{
	bReplicates = true;
	bReplicateUsingRegisteredSubObjectList = true;
}

void AMasterWeaponRanged::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ProjectileFactory = NewObject<UBulletProjectileFactory>();
}

void AMasterWeaponRanged::BeginPlay()
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

void AMasterWeaponRanged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMasterWeaponRanged::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMasterWeaponRanged, bIsStartShooting);
	DOREPLIFETIME(AMasterWeaponRanged, WeaponDataAssetRef);
	DOREPLIFETIME(AMasterWeaponRanged, RoundsInMagazine);
	DOREPLIFETIME(AMasterWeaponRanged, SelectedFireMode);
}

void AMasterWeaponRanged::InitWeaponBaseData(UWeaponDataAsset* NewWeaponDataAsset)
{
	Super::InitWeaponBaseData(NewWeaponDataAsset);

	if (HasAuthority())
	{
		WeaponDataAssetRef = NewWeaponDataAsset;

		SelectedFireMode = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.AvailableShootingModes[0];
		if (!WeaponDataAssetRef->CharacteristicsOfRangedWeapon.UsableAmmo.IsEmpty())
		{
			TArray<UAmmoBase*> tempAmmo;
			for (auto Element : WeaponDataAssetRef->CharacteristicsOfRangedWeapon.UsableAmmo)
			{
				const FAmmoData* AData = Element.DataTable->FindRow<FAmmoData>(
					Element.RowName, Element.RowName.ToString());
				if (!AData)
					continue;

				UAmmoBase* AmmoBase = NewObject<UAmmoBase>(this, UAmmoBase::StaticClass());
				AmmoBase->SetAmmoData(AData->AmmoCharacteristics, AData->AmmoBehaviour, AData->AmmoAssets);

				tempAmmo.Add(AmmoBase);
			}
			if (tempAmmo.Num() > 0)
			{
				SelectedAmmoData = tempAmmo[0];
				UsableAmmo = tempAmmo;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Error: No usable ammo found after processing."));
			}
		}

		StartReload();
		UpdateVisual();
	}
	
	if (WeaponDataAssetRef && WeaponDataAssetRef->GrantedAbilities.Num() > 0)
	{
		auto It = WeaponDataAssetRef->GrantedAbilities.CreateConstIterator();
		const auto FirstKey = It->Key;
		const auto FirstValue = It->Value;
		
		CurrentAttackAbilityClass= FirstKey;
		CurrentAbilityData = FirstValue;
	}
}

void AMasterWeaponRanged::UpdateVisual()
{
	Super::UpdateVisual();
}

FVector AMasterWeaponRanged::GetProjectileSpawnLocation()
{
	FVector SpawnLocation;

	if (bOwnerIsPlayer && WeaponDataAssetRef->bTraceFromCamera)
	{
		SpawnLocation = OwnerCamera->K2_GetComponentLocation();
	}
	else
	{
		FTransform BulletSpawnPointTransform;
		if (SkeletalMeshWeapon->GetSkinnedAsset())
			BulletSpawnPointTransform = GetMuzzleTransform(CurrentAbilityData.ShootActionData.BulletSpawnSocketTransformName, SkeletalMeshWeapon);
		else if (StaticMeshWeapon->GetStaticMesh())
			BulletSpawnPointTransform = GetMuzzleTransform(CurrentAbilityData.ShootActionData.BulletSpawnSocketTransformName, StaticMeshWeapon);
		
		SpawnLocation = BulletSpawnPointTransform.GetLocation();
		
	}

	return SpawnLocation;
}

bool AMasterWeaponRanged::IsCanStartReload()
{
	if (RoundsInMagazine >= GetMagazineSize())
		return false;

	return true;
}

void AMasterWeaponRanged::StartReload()
{
	if (HasAuthority())
	{
		RoundsInMagazine = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.MagazineSize;
		OnRep_RoundsInMagazine();
	}
	else
	{
		ServerReload();
	}
}

FAttackReadyResult AMasterWeaponRanged::CheckIsCanAttack()
{
	if (RoundsInMagazine <= 0)
		return FAttackReadyResult(EAttackReadyStatus::NoAmmo, TEXT("No ammo left."));

	if (GetWorld()->GetTimerManager().IsTimerActive(ShootDelayTimerHandle))
		return FAttackReadyResult(EAttackReadyStatus::AttackDelayActive, TEXT("Attack delay timer is active."));

	if (AvailableShootsCount <=0)
		return FAttackReadyResult(EAttackReadyStatus::FireSequenceEmpty, TEXT("FireSequenceEmpty"));

	if (bIsReadyToNextShoot && AvailableShootsCount > 0)
	{
		//FString Message = FString::Printf(TEXT("Available Shoots Count: %d"), AvailableShootsCount);
		//UKismetSystemLibrary::PrintString(this, Message, true, false, FLinearColor::Yellow, 5.0f);

		if (!bIsStartShooting)
		{
			bIsStartShooting = true;
		}

		FString ReadyMessage = FString::Printf(TEXT("Weapon is ready. Available shoots: %d"), AvailableShootsCount);
		return FAttackReadyResult(EAttackReadyStatus::Ready, ReadyMessage);
	}

	return FAttackReadyResult(EAttackReadyStatus::Unknown, TEXT("Unknown shoot readiness state."));
}

void AMasterWeaponRanged::InitializeFireSequence()
{
	switch (SelectedFireMode)
	{
	case EFireMode::Single:
		AvailableShootsCount = 1;
		break;
	case EFireMode::Burst:
		AvailableShootsCount = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.ShotsPerBurst;
		break;
	case EFireMode::Full_Auto:
		AvailableShootsCount = GetRoundsInMagazine();
		break;
	default:
		break;
	}

	OnStartFireSignatureDelegate.Broadcast();
	OnStartFire();
}

void AMasterWeaponRanged::StopFireSequence()
{
	bIsStartShooting = false;
	OnStopFireDelegate.Broadcast();
	OnStopFire();
}

void AMasterWeaponRanged::SwitchAttackMode()
{
	SwitchFireMode();

	if (OnSwitchFireModeDelegate.IsBound())
	{
		OnSwitchFireModeDelegate.Broadcast(GetSelectedFireMode());
	}
}

void AMasterWeaponRanged::InitializeAttackSequence()
{
	InitializeFireSequence();
}

void AMasterWeaponRanged::StopAttackSequence()
{
	StopFireSequence();
}

void AMasterWeaponRanged::AttackTrigger(TSubclassOf<UGameplayAbility> AbilityClass)
{
	CurrentAttackAbilityClass = AbilityClass;
	if (const FWeaponAbilityData* FoundData = WeaponDataAssetRef->GrantedAbilities.Find(CurrentAttackAbilityClass))
		CurrentAbilityData = *FoundData;
	StartFireWeapon();
}

void AMasterWeaponRanged::AimTrigger()
{
	if (WeaponDataAssetRef->ShowTrace)
	{
		ShowTrajectory();
	}
}

void AMasterWeaponRanged::StartFireWeapon()
{
	OnFire();
	DecreaseRoundsInMagazine();

	switch (WeaponDataAssetRef->BulletMode)
	{
	case EBulletMode::HitScan:
		break;
	case EBulletMode::Projectile:
		if (CurrentAbilityData.ShootActionData.DelayBeforeSpawnBullet > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(SpawnBulletDelay, [this]()
			{
				ConfigureSpawnedProjectile();
		
			}, CurrentAbilityData.ShootActionData.DelayBeforeSpawnBullet, false);
			break;
		}
		
		ConfigureSpawnedProjectile();
		break;
	default:
		break;
	}

	AvailableShootsCount--;

	bIsReadyToNextShoot = false;

	GetWorld()->GetTimerManager().SetTimer(ShootDelayTimerHandle, [this]()
	{
		bIsReadyToNextShoot = true;
	}, 60.0f / WeaponDataAssetRef->CharacteristicsOfRangedWeapon.RPM, false);
}

void AMasterWeaponRanged::ConfigureSpawnedProjectile()
{
	if ( CurrentAbilityData.ShootActionData.BulletActorClass)
	{
		BulletActorClass = CurrentAbilityData.ShootActionData.BulletActorClass;
		if (!SelectedAmmoData)
		{
			UE_LOG(LogTemp, Error, TEXT("Error: No usable ammo found"))
			return;
		}

		auto AmmoCharacteristics = SelectedAmmoData->GetAmmoCharacteristics();
		for (int i = 0; i < AmmoCharacteristics.NumberOfShotsPerRound; i++)
		{
			// Spreading angle
			auto SpreadAngle = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.SpreadAngle;
			// Отклонение для разброса
			FRotator RandomSpread = FRotator(
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Pitch
				FMath::RandRange(-SpreadAngle, SpreadAngle), // Yaw
				0.0f // Roll (не нужно для разброса)
			);

			FVector SpawnLocation = GetProjectileSpawnLocation();
			FRotator SpawnRotation;
			/*if (bOwnerIsPlayer && WeaponDataAssetRef->bTraceFromCamera)
			{
				SpawnRotation = OwnerCamera->GetComponentRotation();
			}
			else*/
			{
				auto BulletSpawnPointTransform =
					GetMuzzleTransform(CurrentAbilityData.ShootActionData.BulletSpawnSocketTransformName, SkeletalMeshWeapon);
				SpawnRotation = BulletSpawnPointTransform.GetRotation().Rotator();
				//SpawnRotation = BulletSpawnPointTransform.GetRotation().Rotator() + RandomSpread;
			}

			SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation,TargetPoint) + RandomSpread;

			ServerProjectileSpawn(SpawnLocation, SpawnRotation, AmmoCharacteristics);
			if (OnSpawnedProjectile.IsBound())
				OnSpawnedProjectile.Broadcast(RoundsInMagazine);
		}
	}
}

void AMasterWeaponRanged::ServerProjectileSpawn_Implementation(const FVector& SpawnLocation,
                                                               const FRotator& SpawnRotation,
                                                               const FAmmoCharacteristics& AmmoCharacteristics)
{
	HandleProjectileSpawn(SpawnLocation, SpawnRotation);
}

void AMasterWeaponRanged::HandleProjectileSpawn(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	if (!ProjectileFactory)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectileFactory is not valid."));
		return;
	}

	const FActorSpawnParameters SpawnParameters;
	auto NewBulletAmmoData = SelectedAmmoData;


	auto SpawnedActorRef = ProjectileFactory->CreateProjectile(GetWorld(), BulletActorClass, SpawnLocation,
	                                                           SpawnRotation, SpawnParameters);
	if (SpawnedActorRef)
	{
		SpawnedActorRef->SetActorTickEnabled(false);
		SpawnedActorRef->SetActorHiddenInGame(true);
		SpawnedActorRef->SetOwner(Owner);

		auto BulletActor = Cast<ABaseBulletActor>(SpawnedActorRef);
		if (!BulletActor)
		{
			SpawnedActorRef->Destroy();
			return;
		};

		BulletActor->BulletFlightMode = CurrentAbilityData.ShootActionData.BulletFlightMode;
		BulletActor->ActorsToIgnore.Add(WeaponOwnerActor);

		switch (BulletActor->BulletFlightMode)
		{
		case EBulletFlightMode::Physical:
			//UE_LOG(LogTemp, Error, TEXT("Error: Owner of SpawnedActorRef is %s"), *Owner->GetName());
			if (!SelectedAmmoData)
			{
				UE_LOG(LogTemp, Error, TEXT("Error: Selected ammo data is null in %s"), *GetOwner()->GetName());
				break;
			}
			BulletActor->SelectedAmmoData = NewBulletAmmoData;
			break;

		case EBulletFlightMode::Parabolic:
			if (!SelectedAmmoData)
			{
				UE_LOG(LogTemp, Error, TEXT("Error: Selected ammo data is null in %s"), *GetOwner()->GetName());
				break;
			}
			BulletActor->SelectedAmmoData = NewBulletAmmoData;
			if (bOwnerIsPlayer)
			{
				BulletActor->SetActorRotation(OwnerCamera->GetForwardVector().Rotation());
			}
			else
			{
				BulletActor->SetActorRotation(WeaponOwnerActor->GetActorForwardVector().Rotation());
				BulletActor->SetAutoAim(true, TargetPoint);
			}
			break;
		}

		SpawnedActorRef->SetActorTickEnabled(true);
		SpawnedActorRef->SetActorHiddenInGame(false);

		BulletActor->InitBullet();
	}
}

void AMasterWeaponRanged::PlayShootEffect(UParticleSystem* ParticleSystem, FName SocketName)
{
	if (!ParticleSystem || !SkeletalMeshWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid ParticleSystem or SkeletalMeshWeapon"));
		return;
	}

	if (HasAuthority())
	{
		PlayShootEffect_Multicast(ParticleSystem, SocketName);
	}
	else
	{
		PlayShootEffect_Server(ParticleSystem, SocketName);
	}
}

void AMasterWeaponRanged::PlayShootEffect_Server_Implementation(UParticleSystem* ParticleSystem, FName SocketName)
{
	PlayShootEffect_Multicast(ParticleSystem, SocketName);
}

void AMasterWeaponRanged::PlayShootEffect_Multicast_Implementation(UParticleSystem* ParticleSystem, FName SocketName)
{
	UParticleSystemComponent* ParticleComponent = UGameplayStatics::SpawnEmitterAttached(
		ParticleSystem, // Шаблон эмиттера
		SkeletalMeshWeapon, // К какому компоненту прикрепляем
		SocketName, // Имя сокета, куда прикрепить
		FVector::ZeroVector, // Локальная позиция
		FRotator::ZeroRotator, // Локальная ротация
		FVector(1.0f, 1.0f, 1.0f), // Масштаб
		EAttachLocation::KeepRelativeOffset, // Тип привязки
		true // Автоматическое уничтожение
	);

	if (!ParticleComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn emitter!"));
	}
}

void AMasterWeaponRanged::DecreaseRoundsInMagazine()
{
	if (WeaponDataAssetRef->CharacteristicsOfRangedWeapon.bInfinityMagazine)
		return;

	if (HasAuthority())
		RoundsInMagazine--;
	else
		ServerDecreaseRoundsInMagazine();
}

void AMasterWeaponRanged::ServerDecreaseRoundsInMagazine_Implementation()
{
	RoundsInMagazine--;
}

void AMasterWeaponRanged::ServerReload_Implementation()
{
	RoundsInMagazine = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.MagazineSize;
}

void AMasterWeaponRanged::SwitchFireMode()
{
	if (SelectedFireMode == EFireMode::None)
	{
		SelectedFireMode = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.AvailableShootingModes[0];
		return;
	}

	int32 CurrentIndex = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.AvailableShootingModes.IndexOfByKey(
		SelectedFireMode);
	CurrentIndex++;
	if (CurrentIndex < WeaponDataAssetRef->CharacteristicsOfRangedWeapon.AvailableShootingModes.Num())
	{
		SelectedFireMode = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.AvailableShootingModes[CurrentIndex];
	}
	else
		SelectedFireMode = WeaponDataAssetRef->CharacteristicsOfRangedWeapon.AvailableShootingModes[0];


	//UE_LOG(LogTemp, Log, TEXT("Fire Mode: %d"), static_cast<int>(SelectedFireMode));
}

void AMasterWeaponRanged::SetWeaponBaseRef(UWeaponDataAsset* NewWeaponDataAsset)
{
	Super::SetWeaponBaseRef(NewWeaponDataAsset);

	InitWeaponBaseData(NewWeaponDataAsset);
}

void AMasterWeaponRanged::OnRep_RoundsInMagazine() const
{
	if (OnCompleteReloadDelegate.IsBound())
		OnCompleteReloadDelegate.Broadcast(RoundsInMagazine);
}

FTransform AMasterWeaponRanged::GetMuzzleTransform(FName SocketName, USceneComponent* OverrideComponent)
{
	if (!WeaponOwnerActor)
		return FTransform::Identity;

	// 1. Проверяем скелетный меш
	if (USkeletalMeshComponent* Skel = WeaponOwnerActor->FindComponentByClass<USkeletalMeshComponent>())
	{
		if (Skel->DoesSocketExist(SocketName))
			return Skel->GetSocketTransform(SocketName, RTS_World);
	}

	for (UActorComponent* C : WeaponOwnerActor->GetComponents())
	{
		if (USceneComponent* SC = Cast<USceneComponent>(C))
		{
			if (SC->GetName() == SocketName.ToString())
			{
				return SC->GetComponentTransform();
			}
		}
	}

	if (OverrideComponent)
	{
		if (OverrideComponent->DoesSocketExist(SocketName))
			return OverrideComponent->GetSocketTransform(SocketName, RTS_World);

		return OverrideComponent->GetComponentTransform();
	}

	return WeaponOwnerActor->GetActorTransform();
}
