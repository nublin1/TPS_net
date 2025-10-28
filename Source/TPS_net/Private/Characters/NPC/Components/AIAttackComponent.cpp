// Nublin Studio 2025 All Rights Reserved.

#include "Characters/NPC/Components/AIAttackComponent.h"

#include "Engine/Engine.h"
#include "Interfaces/IHealthInterface.h"
#include "Kismet/GameplayStatics.h"


UAIAttackComponent::UAIAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ComponentTags.Add(FName("IA_AttackComponentTag"));
}

void UAIAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	if (auto OwnerSkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>())
		SkeletalMeshComponent = OwnerSkeletalMeshComponent;
}

void UAIAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
										   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UAIAttackComponent::RequestHitDetect()
{
	AActor* Owner = GetOwner();
	if (!Owner) return false;

	if (Owner->HasAuthority())
	{
		return HitDetect();
	}

	return false;
}

bool UAIAttackComponent::HitDetect()
{
	AActor* Owner = GetOwner();
	if (!Owner) return false;
	
	if (!SkeletalMeshComponent) return false;

	//AttackSocketName = FName("hand_r");
	SocketLocation = SkeletalMeshComponent->GetSocketLocation(AttackSocketName);
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
	//UE_LOG(LogTemp, Warning, TEXT("ApplyDamage on Server"));
	
	//FVector ShotDirection = (HitActor->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal();    
	//AController* InstigatorController = HitActor->GetInstigatorController();    
	//UGameplayStatics::ApplyPointDamage(HitActor, 10.0f, ShotDirection, nullptr, InstigatorController, GetOwner(), nullptr);
	
	UGameplayStatics::ApplyDamage(HitActor, 10.0f, HitActor->GetInstigatorController(),  GetOwner(), UDamageType::StaticClass());
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
