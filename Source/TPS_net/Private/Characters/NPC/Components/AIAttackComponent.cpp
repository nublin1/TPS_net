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

void UAIAttackComponent::AttackCompleted(UAnimMontage* Montage, bool bInterrupted)
{
	if (EndAttackDelegate.IsBound())
		EndAttackDelegate.Broadcast();
}

void UAIAttackComponent::ServerApplyDamage_Implementation(AActor* HitActor)
{
	if (!HitActor) return;


	UGameplayStatics::ApplyDamage(HitActor, 10.0f, HitActor->GetInstigatorController(), GetOwner(),
	                              UDamageType::StaticClass());
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
		                                             WeaponMeleeAttackData.MeleeAttackRange;
		if (Distance > Attackrange)
			return false;
	}
	else
	{
		TObjectPtr<AMasterWeaponRanged> WeaponInHands = Cast<AMasterWeaponRanged>(WeaponSystemComponentRef->GetCurrentWeaponInHands());
		
		/*auto Attackrange = WeaponInHands->GetWeaponDataAssetRef()->ShootActionData.AttackRange_AI;

		if (Distance > Attackrange)
			return false;
		else
		{
			WeaponInHands->SetTargetPoint(End);
		}*/
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
