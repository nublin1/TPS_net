// Nublin Studio 2025 All Rights Reserved.


#include "World/Weapons/BaseWeapon.h"
#include "AbilitySystemComponent.h"
#include "Data/DamageTypes/DamageType_Knockback.h"
#include "Data/Weapon/WeaponData.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/AmmoBase.h"


ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshWeapon->SetupAttachment(RootScene);

	StaticMeshWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshWeapon->SetupAttachment(RootScene);

	// Trace points
	TraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	TraceStart->SetupAttachment(RootScene);

	TraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	TraceEnd->SetupAttachment(RootScene);

	bReplicates = true;
}

void ABaseWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);
}

void ABaseWeapon::InitWeaponBaseData(UWeaponDataAsset* NewWeaponDataAsset)
{
}

void ABaseWeapon::InitializeGrantedAbilities()
{
	if (WeaponDataAssetRef && !WeaponDataAssetRef->GrantedAbilities.IsEmpty())
	{
		auto It = WeaponDataAssetRef->GrantedAbilities.CreateConstIterator();
        
		CurrentAttackAbilityClass = It->Key;
		CurrentAbilityData = It->Value;
	}
}

void ABaseWeapon::UpdateVisual()
{
	if (!WeaponDataAssetRef)
	{
		UE_LOG(LogTemp, Warning, TEXT(" AMasterWeapon WeaponDataAssetRef is null"));
		return;
	}

	/*if (WeaponDataAssetRef->WeaponType != EWeaponType::Melee)
	{
		return;
	}*/

	if (WeaponDataAssetRef->WeaponPresentationData.SkeletalMesh)
	{
		SkeletalMeshWeapon->SetSkeletalMesh(WeaponDataAssetRef->WeaponPresentationData.SkeletalMesh);
	}
	if (WeaponDataAssetRef->WeaponPresentationData.StaticMesh)
	{
		StaticMeshWeapon->SetStaticMesh(WeaponDataAssetRef->WeaponPresentationData.StaticMesh);
	}

	if (WeaponDataAssetRef->WeaponPresentationData.WeaponAnimationBlueprint)
		SkeletalMeshWeapon->SetAnimInstanceClass(
			WeaponDataAssetRef->WeaponPresentationData.WeaponAnimationBlueprint->GetAnimBlueprintGeneratedClass());
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load animation class"));
	}
}

void ABaseWeapon::ToggleBoneVisibility(FName BoneName)
{
	if (!SkeletalMeshWeapon) return;

	if (bool bIsHidden = SkeletalMeshWeapon->IsBoneHiddenByName(BoneName))
	{
		SkeletalMeshWeapon->UnHideBoneByName(BoneName);
	}
	else
	{
		SkeletalMeshWeapon->HideBoneByName(BoneName, PBO_None);
	}
}

void ABaseWeapon::ChangeRoundsInMagazine(int32 Delta, bool bReloadToFull)
{
}

FVector ABaseWeapon::GetProjectileSpawnLocation()
{
	return FVector::Zero();
}

FVector ABaseWeapon::GetAmmoMeshReloadPosition()
{
	FVector ReloadPosition = FVector::ZeroVector;
	if (SkeletalMeshWeapon->GetSkinnedAsset())
	{
		auto PositSocket =  SkeletalMeshWeapon->GetSocketByName(WeaponDataAssetRef->WeaponPresentationData.AmmoMeshReloadPosition);
		if (PositSocket)
		{
			FTransform Transform = PositSocket->GetSocketTransform(SkeletalMeshWeapon);
			ReloadPosition = Transform.GetLocation();
		}
	}
	
	if (StaticMeshWeapon->GetStaticMesh())
	{
		const UStaticMeshSocket* PositSocket = StaticMeshWeapon->GetStaticMesh()->FindSocket(WeaponDataAssetRef->WeaponPresentationData.AmmoMeshReloadPosition);

		if (PositSocket)
		{
			FTransform TarTransform;
			PositSocket->GetSocketTransform(TarTransform, StaticMeshWeapon);
			ReloadPosition = TarTransform.GetLocation();
		}
	}

	return ReloadPosition;
}

void ABaseWeapon::SetWeaponBaseRef(UWeaponDataAsset* NewWeaponDataAsset)
{
	WeaponDataAssetRef = NewWeaponDataAsset;
}

void ABaseWeapon::UpdateTracePoints()
{
	if (SkeletalMeshWeapon->GetSkinnedAsset())
	{
		const USkeletalMeshSocket* StartSocket = SkeletalMeshWeapon->GetSocketByName("StartTraceSocket");
		const USkeletalMeshSocket* EndSocket   = SkeletalMeshWeapon->GetSocketByName("EndTraceSocket");

		if (StartSocket && TraceStart)
		{
			FTransform StartTransform = StartSocket->GetSocketTransform(SkeletalMeshWeapon);
			TraceStart->SetWorldTransform(StartTransform);
		}

		if (EndSocket && TraceEnd)
		{
			FTransform EndTransform = EndSocket->GetSocketTransform(SkeletalMeshWeapon);
			TraceEnd->SetWorldTransform(EndTransform);
		}
	}

	if (StaticMeshWeapon && StaticMeshWeapon->GetStaticMesh())
	{
		const UStaticMeshSocket* StartSocket = StaticMeshWeapon->GetStaticMesh()->FindSocket("StartTraceSocket");
		const UStaticMeshSocket* EndSocket   = StaticMeshWeapon->GetStaticMesh()->FindSocket("EndTraceSocket");

		if (StartSocket && TraceStart)
		{
			FTransform StartTransform;
			StartSocket->GetSocketTransform(StartTransform, StaticMeshWeapon);
			TraceStart->SetWorldTransform(StartTransform);
		}

		if (EndSocket && TraceEnd)
		{
			FTransform EndTransform;
			EndSocket->GetSocketTransform(EndTransform, StaticMeshWeapon);
			TraceEnd->SetWorldTransform(EndTransform);
		}
	}
}

void ABaseWeapon::OnRep_WeaponDataAssetRef()
{
	UpdateVisual();
}

void ABaseWeapon::HitDetectAOE()
{
	if (!GetWorld()) return;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(WeaponOwnerActor);

	TArray<FHitResult> OutHits;

	bool bHit = GetWorld()->SweepMultiByObjectType(
		OutHits,
		TraceStart->GetComponentLocation(),
		TraceStart->GetComponentLocation(),
		FQuat::Identity,
		FCollisionObjectQueryParams(ObjectTypes),
		FCollisionShape::MakeSphere(CurrentAbilityData.WeaponMeleeAttackData.AoeRadius),
		Params
	);
	
	//if (bShowTrace)
	{
		DrawDebugSphere(
			GetWorld(),
			TraceStart->GetComponentLocation(),
			CurrentAbilityData.WeaponMeleeAttackData.AoeRadius,
			24,
			bHit ? FColor::Red : FColor::Green,
			false,
			3.0f
		);
	}

	if (!bHit) return;

	TSet<AActor*> DamagedActors;
	TSet<AActor*> IgnoreActors;
	IgnoreActors.Add(WeaponOwnerActor);
	
	for (const FHitResult& Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor || HitActor == GetOwner())
			continue;
		
		FHitResult LOSHit;
		FCollisionQueryParams LOSParams;
		LOSParams.AddIgnoredActor(this);
		LOSParams.AddIgnoredActor(WeaponOwnerActor);
		LOSParams.AddIgnoredActor(HitActor);

		const FVector TargetLocation =
			HitActor->GetActorLocation();

		bool bBlocked = GetWorld()->LineTraceSingleByChannel(
			LOSHit,
			WeaponOwnerActor->GetActorLocation(),
			TargetLocation,
			ECC_Visibility,
			LOSParams
		);

		if (bBlocked)
			continue;

		DamagedActors.Add(HitActor);
	}

	if (DamagedActors.Num() == 0)
		return;

	// --- Radial Damage ---
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		CurrentAbilityData.WeaponMeleeAttackData.AoeDamage,
		TraceStart->GetComponentLocation(),
		CurrentAbilityData.WeaponMeleeAttackData.AoeRadius,
		CurrentAbilityData.WeaponMeleeAttackData.DamageTypeClass,
		IgnoreActors.Array(),
		this,
		WeaponOwnerActor->GetInstigatorController(),
		true // bDoFullDamage
	);
}

void ABaseWeapon::HitDetect()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(WeaponOwnerActor);
	Params.AddIgnoredActor(this);

	TArray<FHitResult> OutHits;
	bool bHit = GetWorld()->SweepMultiByObjectType(
		OutHits,
		TraceStart->GetComponentLocation(),
		TraceEnd->GetComponentLocation(),
		FQuat::Identity,
		FCollisionObjectQueryParams(ObjectTypes),
		FCollisionShape::MakeSphere(CurrentAbilityData.WeaponMeleeAttackData.TraceRadiusImpact),
		Params
	);
	
	if (bShowTrace)
	{
		const FVector Start = TraceStart->GetComponentLocation();
		const FVector End   = TraceEnd->GetComponentLocation();
		
		DrawDebugLine(GetWorld(), Start, End, 
			bHit ? FColor::Green : FColor::Red,
			false, 0.1f, 0, 2.0f);
	}

	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		auto OwnerClass = GetOwner()->GetClass();

		if (HitActor && !HitTargets.Contains(HitActor) && !HitActor->IsA(OwnerClass))
		{
			HitTargets.Add(HitActor, Hit);
			//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
		}
	}

	if (HitTargets.Num() <= 0)
	{
		return;
	}
	for (auto& Hit : HitTargets)
	{
		AActor* HitActor = Hit.Key;
		if (!HitActor) continue;

		UGameplayStatics::ApplyPointDamage(
		HitActor,
		WeaponDataAssetRef->WeaponType == EWeaponType::Ranged ? SelectedAmmoData->GetAmmoCharacteristics().ImpactDamage :CurrentAbilityData.WeaponMeleeAttackData.ImpactDamage,
		(Hit.Value.TraceStart - Hit.Value.TraceEnd).GetSafeNormal(),
		Hit.Value,
		GetOwner()->GetInstigatorController(),
		this,
		UDamageType::StaticClass()
	);
		
		/*UAbilitySystemComponent* ASC = HitActor->FindComponentByClass<UAbilitySystemComponent>();
		{
			FGameplayEffectSpec* Spec = GameplayEffectSpecHandle.Data.Get();
			if (!Spec)
				continue;
			
			ASC->ApplyGameplayEffectSpecToSelf(*Spec);
			Hit.Value = true;
		}*/
	}
}

void ABaseWeapon::HitDetectStart(bool NewShowTrace)
{
	HitTargets.Empty();

	GetWorld()->GetTimerManager().SetTimer(HitDetectTimer, this, &ABaseWeapon::HitDetect, 0.03f, true);
	
	bShowTrace = NewShowTrace;
}

void ABaseWeapon::HitDetectEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(HitDetectTimer);

	bShowTrace = false;
}