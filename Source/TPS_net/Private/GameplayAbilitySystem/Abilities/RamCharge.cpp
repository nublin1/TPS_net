// Nublin Studio 2026 All Rights Reserved.


#include "GameplayAbilitySystem/Abilities/RamCharge.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

URamCharge::URamCharge()
{
}

void URamCharge::StartChargeTrace()
{
	if (!GetWorld())
	{
		return;
	}

	if (!GetCurrentActorInfo()->IsNetAuthority())
	{
		return;
	}

	HitActorsHistory.Empty();
	
	GetWorld()->GetTimerManager().SetTimer(
		TraceTimer,
		this,
		&URamCharge::DoTrace,
		TraceInterval,
		true
	);
}

void URamCharge::StopChargeTrace()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TraceTimer);
	}
}

void URamCharge::StartDistanseCheck()
{
	if (!GetWorld())
	{
		return;
	}

	if (!GetCurrentActorInfo()->IsNetAuthority())
	{
		return;
	}

	LastLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	TravelledDistance = 0.f;

	GetWorld()->GetTimerManager().SetTimer(
		DistanseTimer,
		this,
		&URamCharge::DoDistanseCheck,
		DistanseInterval,
		true
	);
}

void URamCharge::StopDistanseCheck()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DistanseTimer);
	}
}

void URamCharge::DoTrace()
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!Character) return;

	FVector Start = Character->GetActorLocation();
	FVector End = Start + Character->GetActorForwardVector() * ForwardSweepLength;

	FCollisionShape Shape = FCollisionShape::MakeCapsule(
	   Character->GetCapsuleComponent()->GetScaledCapsuleRadius(),
	   Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
	);

	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_Pawn, Shape);
	
	TSet<AActor*> ActorsHitThisTick;
	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActorPtr = Hit.GetActor();
		if (!HitActorPtr || HitActorPtr == Character) continue;

		// (WorldStatic)
		if (Hit.Component.IsValid() && Hit.Component->GetCollisionObjectType() == ECC_WorldStatic)
		{
			HitWall();
			continue; 
		}
		
		if (ActorsHitThisTick.Contains(HitActorPtr)) continue;
		ActorsHitThisTick.Add(HitActorPtr);
		
		if (bUniqueHitsPerCharge)
		{
			if (HitActorsHistory.Contains(HitActorPtr)) continue;
			HitActorsHistory.Add(HitActorPtr);
		}
		
		HitActor(HitActorPtr);
	}
}

void URamCharge::DoDistanseCheck()
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	FVector CurrentLocation = Avatar->GetActorLocation();

	float Delta = FVector::Dist(CurrentLocation, LastLocation);
	TravelledDistance += Delta;

	LastLocation = CurrentLocation;

	if (TravelledDistance >= MaxChargeDistance)
	{
		HasReachedDistance();
	}
}
