// Nublin Studio 2025 All Rights Reserved.


#include "Componets/Sense/NPCSenseComponent.h"

// Sets default values for this component's properties
UNPCSenseComponent::UNPCSenseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UNPCSenseComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Sense, this, &UNPCSenseComponent::PerformSenseCheck, UpdateInterval, true);
}

void UNPCSenseComponent::PerformSenseCheck()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Owner->GetActorLocation(),
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(SenseRadius),
		Params
	);

	for (auto& Result : Overlaps)
	{
		AActor* Other = Result.GetActor();
		if (!Other || Other == Owner) continue;

		bool bClassAllowed = false;
		
		// Проверка класса
		if (DetectableClasses.Num() > 0)
		{
			bClassAllowed = false;
			for (auto DetectClass : DetectableClasses)
			{
				if (Other->GetClass()->IsChildOf(DetectClass))
				{
					bClassAllowed = true;
					break;
				}
			}
			if (!bClassAllowed) continue;
		}

		if (!bClassAllowed)
			continue;

		if (IsInViewCone(Other) && HasLineOfSight(Other))
		{
			OnActorSensed.Broadcast(Other);
		}
	}
}

bool UNPCSenseComponent::IsInViewCone(AActor* OtherActor) const
{
	if (!OtherActor) return false;

	FVector ToTarget = (OtherActor->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();
	FVector Forward = GetOwner()->GetActorForwardVector();
	float Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(Forward, ToTarget)));

	return Angle <= VisionAngle * 0.5f;
}

bool UNPCSenseComponent::HasLineOfSight(AActor* OtherActor) const
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FVector Start = GetOwner()->GetActorLocation();
	FVector End = OtherActor->GetActorLocation();

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, Params);

	return !bHit || Hit.GetActor() == OtherActor;
}

void UNPCSenseComponent::SetSensingEnabled(bool bEnable)
{
	if (bIsSensingEnabled == bEnable)
		return;

	bIsSensingEnabled = bEnable;

	if (bIsSensingEnabled)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Sense, this,  &UNPCSenseComponent::PerformSenseCheck, UpdateInterval, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Sense);
	}
}
