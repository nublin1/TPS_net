// Nublin Studio 2025 All Rights Reserved.

#include "World/Builds/Turret.h"

#include "Componets/Sense/NPCSenseComponent.h"
#include "Kismet/KismetMathLibrary.h"


ATurret::ATurret(): RotatingMesh(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	//SenseComponent = CreateDefaultSubobject<UNPCSenseComponent>(TEXT("SenseComponent"));
	//SenseComponent->OnComponentCreated();
	//SenseComponent->SetIsReplicated(true);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	StartYaw = GetActorRotation().Yaw;
	StartYaw = UKismetMathLibrary::NormalizeAxis(StartYaw);

	if (!RotatingMesh)
	{
		if (USceneComponent* Found = Cast<USceneComponent>(
			FindComponentByTag(USceneComponent::StaticClass(), RotatingComponentTag)))
		{
			RotatingMesh = Found;
			
			StartYaw = RotatingMesh->GetRelativeRotation().Yaw; 
			StartYaw = UKismetMathLibrary::NormalizeAxis(StartYaw);
		}
	}
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!RotatingMesh)
		return;

	if (CurrentTarget)
	{
		RotationToTarget(DeltaTime);
		if (bIsAimed)
			PerformAttack();
	}
	else
	{
		IdleRotation(DeltaTime);
	}
}

void ATurret::RotationToTarget(float DeltaTime)
{
	// Расчет требуемого угла к цели (Target Yaw)	
	FVector StartLocation = RotatingMesh->GetComponentLocation();
	FVector TargetLocation = CurrentTarget->GetActorLocation();

	FVector Direction = TargetLocation - StartLocation;
	float RequiredWorldYaw = Direction.Rotation().Yaw;
	float RequiredLocalComponentYaw = FMath::FindDeltaAngleDegrees(
		GetActorRotation().Yaw, 
		RequiredWorldYaw
	);

	//
	float DeltaFromStart = FMath::FindDeltaAngleDegrees(
		StartYaw, 
		RequiredLocalComponentYaw
	);

	float ClampedDeltaFromStart = FMath::Clamp(DeltaFromStart, -MaxYawLimit, MaxYawLimit);
	float FinalTargetLocalYaw = StartYaw + ClampedDeltaFromStart;

	//
	FRotator CurrentLocalRotation = RotatingMesh->GetRelativeRotation();
	float NewYaw = FMath::FInterpConstantTo(
	   CurrentLocalRotation.Yaw,
	   FinalTargetLocalYaw,
	   DeltaTime,
	   RotationRate 
	);
	
	FRotator NewLocalRotation = CurrentLocalRotation;
	NewLocalRotation.Yaw = NewYaw;

	RotatingMesh->SetRelativeRotation(NewLocalRotation);

	float DeltaYawToTarget = FMath::FindDeltaAngleDegrees(
		RotatingMesh->GetRelativeRotation().Yaw,
		FinalTargetLocalYaw);

	bIsAimed = FMath::Abs(DeltaYawToTarget) < AimThreshold;

	if (bIsAimed)
	{
		OnTargetAligned.Broadcast();
	}
	else
	{
		OnTargetAlignedLost.Broadcast();
	}
}

void ATurret::IdleRotation(float DeltaTime)
{
	float DeltaYaw = RotationRate * DeltaTime * RotationDirection;
	FRotator DeltaRotation = FRotator(0.0f, DeltaYaw, 0.0f);
	
	RotatingMesh->AddLocalRotation(DeltaRotation);

	float CurrentYaw = RotatingMesh->GetRelativeRotation().Yaw;
	float DeltaFromStart = FMath::FindDeltaAngleDegrees(StartYaw, CurrentYaw);

	if (RotationDirection > 0.0f && DeltaFromStart >= MaxYawLimit)
	{
		//
		FRotator NewLocalRotation = RotatingMesh->GetRelativeRotation();
		NewLocalRotation.Yaw = StartYaw + MaxYawLimit;
		RotatingMesh->SetRelativeRotation(NewLocalRotation);
		
		RotationDirection = -1.0f;
	}
	else if (RotationDirection < 0.0f && DeltaFromStart <= -MaxYawLimit)
	{
		// 
		FRotator NewLocalRotation = RotatingMesh->GetRelativeRotation();
		NewLocalRotation.Yaw = StartYaw - MaxYawLimit;
		RotatingMesh->SetRelativeRotation(NewLocalRotation);
		
		RotationDirection = 1.0f;
	}
}

