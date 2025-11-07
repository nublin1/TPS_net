// Nublin Studio 2025 All Rights Reserved.

#include "Characters/NPC/Components/AIAttackComponent.h"

#include "Engine/Engine.h"
#include "Interfaces/IHealthInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


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

	if (UAnimInstance* TempAnimInstance = SkeletalMeshComponent->GetAnimInstance())
	{
		AnimInstance = TempAnimInstance;
	}
}

void UAIAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CanStartAttack())
	{
		PerformAttack();
	}
}

void UAIAttackComponent::InitAttackComponent(TArray<FAttackData> Attacks)
{
	if (Attacks.Num() < 0)
		return;
	
	AvailableAttacks = Attacks;
	CurrentAttack = AvailableAttacks[0];
}

void UAIAttackComponent::SetTargetActor(AActor* NewTargetActor)
{
	TargetActor = NewTargetActor;
}

bool UAIAttackComponent::CanStartAttack()
{
	if (!TargetActor || GetWorld()->GetTimerManager().IsTimerActive(TimerHandleAttackPeriod) || !ReadyToAttack)
		return false;

	if (!InRangeToAttack())
		return false;

	return true;
}

void UAIAttackComponent::PerformAttack()
{
	if (!AnimInstance || !CurrentAttack.AttackMontage)
	{
		return;
	}

	switch (CurrentAttack.AttackType)
	{
	case EAttackType::Melee:
		HandleSimpleMeleeAttack();
		break;
	case EAttackType::Ranged:
		HandleRangedAttack();
		break;
	case EAttackType::AOE:
		HandleAOEAttack();
		break;
	case EAttackType::Throw:
		HandleThrowAttack();
		break;
	case EAttackType::SelfDestruct:
		HandleSelfDestruct();
		break;
	default:
		break;
	}
}

void UAIAttackComponent::HandleSimpleMeleeAttack()
{
	if (StartAttackDelegate.IsBound())
		StartAttackDelegate.Broadcast();

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UAIAttackComponent::AttackCompleted);

	AnimInstance->Montage_Play(CurrentAttack.AttackMontage, 1.0f);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, CurrentAttack.AttackMontage);

	GetWorld()->GetTimerManager().SetTimer(TimerHandleAttackPeriod, [this]()
	{
		ReadyToAttack = true;
	}, 2.0f, false);
	
	GetWorld()->GetTimerManager().SetTimer(CurrentAttack.AttackCooldown, [this]()
	{
	}, CurrentAttack.Cooldown, false);
}

void UAIAttackComponent::HandleRangedAttack()
{
	if (StartAttackDelegate.IsBound())
		StartAttackDelegate.Broadcast();

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UAIAttackComponent::AttackCompleted);

	AnimInstance->Montage_Play(CurrentAttack.AttackMontage, 1.0f);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, CurrentAttack.AttackMontage);

	GetWorld()->GetTimerManager().SetTimer(TimerHandleAttackPeriod, [this]()
	{
		ReadyToAttack = true;
	}, 2.0f, false);
	GetWorld()->GetTimerManager().SetTimer(CurrentAttack.AttackCooldown, [this]()
	{
	}, CurrentAttack.Cooldown, false);
}

void UAIAttackComponent::HandleExplosiveAttack()
{
}

void UAIAttackComponent::HandleAOEAttack()
{
}

void UAIAttackComponent::HandleThrowAttack()
{
}

void UAIAttackComponent::HandleSelfDestruct()
{
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

	if (!SkeletalMeshComponent) return false;

	RotateToTarget();

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
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FVector Start = GetOwner()->GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	const float Distance = FVector::Dist(Start, End);
	if (Distance > CurrentAttack.AttackRange)
		return false;

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
