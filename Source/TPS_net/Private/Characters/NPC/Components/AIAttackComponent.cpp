// Nublin Studio 2025 All Rights Reserved.

#include "Characters/NPC/Components/AIAttackComponent.h"

#include "Componets/Weapon/WeaponSystemComponent.h"
#include "Engine/Engine.h"
#include "Interfaces/IHealthInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Weapons/BaseWeapon.h"
#include "World/Weapons/MasterWeaponRanged.h"


UAIAttackComponent::UAIAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ComponentTags.Add(FName("IA_AttackComponentTag"));
}

void UAIAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAIAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetActor && InRangeToAttack())
	{
		PerformAttack();
	}
}

void UAIAttackComponent::InitAttackComponent()
{
	if (auto WeaponSystem = GetOwner()->FindComponentByClass<UWeaponSystemComponent>())
		WeaponSystemComponentRef = WeaponSystem;
}

void UAIAttackComponent::SetTargetActor(AActor* NewTargetActor)
{
	TargetActor = NewTargetActor;
}

void UAIAttackComponent::PerformAttack_Implementation()
{
	RotateToTarget();
	WeaponSystemComponentRef->AiPerformAttack();
}

void UAIAttackComponent::AttackCompleted(UAnimMontage* Montage, bool bInterrupted)
{
	if (EndAttackDelegate.IsBound())
		EndAttackDelegate.Broadcast();
}

void UAIAttackComponent::RequestHitDetect()
{
	AActor* Owner = GetOwner();
	if (!Owner || !TargetActor)
		return;

	if (Owner->HasAuthority())
	{
		HitDetect();
	}
	else
	{
		Server_HitDetect();
	}
}

bool UAIAttackComponent::HitDetect()
{
	AActor* Owner = GetOwner();
	if (!Owner) return false;

	//if (!SkeletalMeshComponent) return false;

	

	//AttackSocketName = FName("hand_r");
	//SocketLocation = SkeletalMeshComponent->GetSocketLocation(AttackSocketName);
	FVector TraceStart = SocketLocation;
	FVector TraceEnd = TraceStart;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	TArray<FHitResult> OutHits;

	// Multi Sphere Trace
	bool bHit = GetWorld()->SweepMultiByObjectType(
		OutHits,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		FCollisionObjectQueryParams(ObjectTypes),
		FCollisionShape::MakeSphere(TraceRadius),
		Params
	);

	if (IsDebug)
	{
		if (bHit)
		{
			DrawDebugSphere(GetWorld(), TraceStart, TraceRadius, 12, FColor::Green, false, 1.0f);
		}
		else
		{
			DrawDebugSphere(GetWorld(), TraceStart, TraceRadius, 12, FColor::Red, false, 1.0f);
		}
	}

	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		auto OwnerClass = GetOwner()->GetClass();

		if (HitActor && !AlreadyHitTargets.Contains(HitActor) && !HitActor->IsA(OwnerClass))
		{
			AlreadyHitTargets.Add(HitActor, false);
			//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
		}
	}

	if (AlreadyHitTargets.Num() <= 0)
	{
		return false;
	}
	for (auto& Hit : AlreadyHitTargets)
	{
		if (Hit.Key->Implements<UIHealthInterface>() && Hit.Value == false)
		{
			ServerApplyDamage(Hit.Key);
			Hit.Value = true;
		}
	}

	return true;
}

void UAIAttackComponent::Server_HitDetect_Implementation()
{
	HitDetect();
}

void UAIAttackComponent::ServerApplyDamage_Implementation(AActor* HitActor)
{
	if (!HitActor) return;


	UGameplayStatics::ApplyDamage(HitActor, 10.0f, HitActor->GetInstigatorController(), GetOwner(),
	                              UDamageType::StaticClass());
}

void UAIAttackComponent::ClearAlreadyHitTargets()
{
	if (GetOwner()->HasAuthority())
	{
		AlreadyHitTargets.Empty();
		return;
	}
}

void UAIAttackComponent::ServerClearAlreadyHitTargets_Implementation()
{
	AlreadyHitTargets.Empty();
}

bool UAIAttackComponent::InRangeToAttack() const
{
	if (!WeaponSystemComponentRef)
	{
		return false;
	}

	if (!WeaponSystemComponentRef->bIsAnyWeaponInHands())
		return false;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FVector Start = GetOwner()->GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	const float Distance = FVector::Dist(Start, End);

	if (WeaponSystemComponentRef->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->WeaponType == EWeaponType::Melee)
	{
		auto Attackrange = WeaponSystemComponentRef->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->
		                                             CharacteristicsOfTheWeaponMelee.MeleeAttackRange;
		if (Distance > Attackrange)
			return false;
	}
	else
	{
		TObjectPtr<AMasterWeaponRanged> WeaponInHands = Cast<AMasterWeaponRanged>(WeaponSystemComponentRef->GetCurrentWeaponInHands());
		
		auto Attackrange = WeaponInHands->GetWeaponDataAssetRef()->CharacteristicsOfTheWeapon.AttackRange;

		if (Distance > Attackrange)
			return false;
		else
		{
			WeaponInHands->SetTargetPoint(End);
		}
	}


	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, Params);

	return !bHit || Hit.GetActor() == TargetActor;
}

void UAIAttackComponent::RotateToTarget()
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(),
	                                                                 TargetActor->GetActorLocation());
	FRotator YawOnlyRotation(0.f, LookAtRotation.Yaw, 0.f);
	GetOwner()->SetActorRotation(YawOnlyRotation);
}
