// Nublin Studio 2025 All Rights Reserved.


#include "Componets/Bullets/ProjectileArc.h"


UProjectileArc::UProjectileArc(): PreviousLocation(), StartLocation(), TargetLocation()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UProjectileArc::BeginPlay()
{
	Super::BeginPlay();
}

void UProjectileArc::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bLaunched)
		return;

	TravelT += DeltaTime / TotalFlightTime;

	// Интерполяция позиции между началом и целью по XY
	FVector FlatStart = FVector(StartLocation.X, StartLocation.Y, 0.f);
	FVector FlatEnd = FVector(TargetLocation.X, TargetLocation.Y, 0.f);

	FVector FlatPos = FMath::Lerp(FlatStart, FlatEnd, TravelT);

	// Расчёт высоты по параболе
	// Используем LaunchAngle для определения максимальной высоты
	float Height = FMath::Sin(LaunchAngleRad) * FVector::Dist2D(StartLocation, TargetLocation) * 0.5f;

	// y = 4h * t * (1 - t)
	float ZOffset = 4 * Height * TravelT * (1 - TravelT);

	// Финальная позиция
	FVector NewLocation = FlatPos;
	NewLocation.Z = FMath::Lerp(StartLocation.Z, TargetLocation.Z, TravelT) + ZOffset;

	GetOwner()->SetActorLocation(NewLocation);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		PreviousLocation,
		NewLocation,
		CollisionChannel,
		Params
	);

#if WITH_EDITOR
	// Отладка
	DrawDebugLine(GetWorld(), PreviousLocation, NewLocation, FColor::Yellow, false, 1.f);
#endif
	
	if (Hit.bBlockingHit)
	{
		OutHit = Hit;
		HitDetected();
	}

	//поворот по направлению движения
	FVector Vel = (NewLocation - GetOwner()->GetActorLocation()).GetSafeNormal();
	FRotator NewRot = FRotationMatrix::MakeFromX(Vel).Rotator();
	GetOwner()->SetActorRotation(NewRot);

	PreviousLocation = NewLocation;
}

void UProjectileArc::Launch(const FVector& Start, const FVector& Target, float MaxRange, float MaxAngle)
{
	if (Start.Equals(Target))
		return;

	StartLocation = Start;
	TargetLocation = Target;

	float Distance = FVector::Dist2D(Start, Target);
	NormalizedDistance = FMath::Clamp(Distance / MaxRange, 0.f, 1.f);

	// Вычисляем угол (при макс. расстоянии = MaxAngle, при близком — меньше)
	float AngleDeg = MaxAngle * NormalizedDistance;
	LaunchAngleRad = FMath::DegreesToRadians(AngleDeg);

	// Время полета рассчитываем пропорционально расстоянию (скорость влияет только на скорость движения)
	TotalFlightTime = Distance / MoveSpeed;

	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActors(ActorsToIgnore);

	bLaunched = true;
	TravelT = 0.f;

	GetOwner()->SetActorLocation(StartLocation);
	PreviousLocation = GetOwner()->GetActorLocation();
}

void UProjectileArc::HitDetected()
{
	if(HitResultDelegate.IsBound())
	{
		HitResultDelegate.Broadcast(OutHit);
	}
}

