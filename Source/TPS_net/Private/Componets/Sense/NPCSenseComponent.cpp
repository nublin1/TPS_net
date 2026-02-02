// Nublin Studio 2025 All Rights Reserved.


#include "Componets/Sense/NPCSenseComponent.h"
#include "Engine/OverlapResult.h"
#include "Data/Characters/CharacterStructs.h"

// Sets default values for this component's properties
UNPCSenseComponent::UNPCSenseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNPCSenseComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Sense, this, &UNPCSenseComponent::PerformSenseCheck,
	                                       UpdateInterval, true);

	if (!ViewComponent)
	{
		if (USceneComponent* Found = Cast<USceneComponent>(
			GetOwner()->FindComponentByTag(USceneComponent::StaticClass(), ViewComponentTag)))
		{
			ViewComponent = Found;
			//UE_LOG(LogTemp, Log, TEXT("[%s] SenseComponent: Found ViewComponent '%s'"), *GetOwner()->GetName(), *ViewComponentTag.ToString());
		}
	}
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
		GetViewLocation(),
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(SenseRadius),
		Params
	);

	if (bDrawDebug)
	{
		DrawDebugSphere(
			GetWorld(),
			Owner->GetActorLocation(),
			SenseRadius,
			16, // количество сегментов
			FColor::Yellow,
			false, // перманентное отображение
			UpdateInterval * 0.9f, // время жизни
			0,
			1.f // толщина линий
		);


		FVector Forward = GetViewForward();
		FVector Location = GetViewLocation();
		float HalfAngle = VisionAngle * 0.5f;

		FVector RightLimit = Forward.RotateAngleAxis(HalfAngle, FVector::UpVector);
		FVector LeftLimit = Forward.RotateAngleAxis(-HalfAngle, FVector::UpVector);

		DrawDebugLine(GetWorld(), Location, Location + RightLimit * SenseRadius, FColor::Cyan, false,
		              UpdateInterval * 0.9f, 0, 1.f);
		DrawDebugLine(GetWorld(), Location, Location + LeftLimit * SenseRadius, FColor::Cyan, false,
		              UpdateInterval * 0.9f, 0, 1.f);
	}

	TArray<TObjectPtr<AActor>> OverlapedActors;

	for (auto& OverlapResult : Overlaps)
	{
		AActor* Other = OverlapResult.GetActor();
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

		bool InViewCone = IsInViewCone(Other);
		bool LineOfSight = HasLineOfSight(Other);

		if (bDrawDebug)
		{
			const FVector Start = GetOwner()->GetActorLocation();
			const FVector End = Other->GetActorLocation();
			const FColor LineColor = LineOfSight ? FColor::Green : FColor::Red;

			DrawDebugLine(GetWorld(), Start, End, LineColor, false, UpdateInterval * 0.9f, 0, 1.5f);
		}

		if (InViewCone && LineOfSight)
		{
			OverlapedActors.AddUnique(Other);
			DetectedActors.AddUnique(Other);
			OnActorSensed.Broadcast(Other);
		}
	}

	DetectedActors.RemoveAll([&](AActor* DetectedAc)
	{
		bool bShouldRemove = !OverlapedActors.Contains(DetectedAc);
		if (bShouldRemove)
		{
			OnActorOutOfSense.Broadcast(DetectedAc);
		}
		return bShouldRemove;
	});
}

bool UNPCSenseComponent::IsInViewCone(AActor* OtherActor) const
{
	if (!OtherActor) return false;


	FVector ToTarget = (OtherActor->GetActorLocation() - GetViewLocation()).GetSafeNormal();
	FVector Forward = GetViewForward();
	float Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(Forward, ToTarget)));

	return Angle <= VisionAngle * 0.5f;
}

bool UNPCSenseComponent::HasLineOfSight(AActor* OtherActor) const
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FVector Start = GetViewLocation();
	FVector End = OtherActor->GetActorLocation();

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, Params);

	return !bHit || Hit.GetActor() == OtherActor;
}

FVector UNPCSenseComponent::GetViewLocation() const
{
	if (ViewComponent)
		return ViewComponent->GetComponentLocation();

	return GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
}

FVector UNPCSenseComponent::GetViewForward() const
{
	if (ViewComponent)
		return ViewComponent->GetForwardVector();

	return GetOwner() ? GetOwner()->GetActorForwardVector() : FVector::ForwardVector;
}

void UNPCSenseComponent::InitSense(FSenseData SenseData)
{
	SenseRadius = SenseData.SenseRadius;
	VisionAngle = SenseData.VisionAngle;
	UpdateInterval = SenseData.UpdateInterval;
	TraceChannel = SenseData.TraceChannel;
	DetectableClasses = SenseData.DetectableClasses;
}

void UNPCSenseComponent::SetSensingEnabled(bool bEnable)
{
	if (bIsSensingEnabled == bEnable)
		return;

	bIsSensingEnabled = bEnable;

	if (bIsSensingEnabled)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Sense, this, &UNPCSenseComponent::PerformSenseCheck,
		                                       UpdateInterval, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Sense);
	}
}
