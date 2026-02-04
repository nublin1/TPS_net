// Nublin Studio 2026 All Rights Reserved.


#include "GameplayAbilitySystem/Abilities/JumpAttackAbility.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UJumpAttackAbility::UJumpAttackAbility()
{
}

float UJumpAttackAbility::GetDistanceToGround() const
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!Character) return -1.f;

	FVector Start = Character->GetActorLocation();
	// Смещение луча под капсулу
	float CapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	Start.Z -= CapsuleHalfHeight;

	FVector End = Start - FVector(0.f, 0.f, 2000.f); // Луч на 20 метров вниз

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		return Hit.Distance;
	}

	return 2000.f;
}

float UJumpAttackAbility::CalculateJumpForce(FVector Start, FVector End, float Duration, FVector& OutDirection)
{
	if (Duration <= 0.f) 
	{
		return 0.0f;
	}
	
	FVector Delta = End - Start;
	
	// СкоростьZ_нужная = (РасстояниеZ + 0.5 * g * t^2) / t
	float GravityZ = FMath::Abs(GetWorld()->GetWorldSettings()->GetGravityZ());
	float RequiredZVelocity = (Delta.Z + (0.5f * GravityZ * FMath::Square(Duration))) / Duration;
	
	// По горизонтали скорость простая: Distance / Time
	FVector FinalVelocity = FVector(Delta.X / Duration, Delta.Y / Duration, RequiredZVelocity);

	// Разделяем на направление и силу
	float Strength = FinalVelocity.Size();
	OutDirection = FinalVelocity.GetSafeNormal();

	return Strength;
}

void UJumpAttackAbility::StartMonitoringLanding()
{
	// Запускаем проверку каждые 0.02 секунды (50 раз в секунду) — это легче, чем полный Tick
	GetWorld()->GetTimerManager().SetTimer(TickTimerHandle, this, &UJumpAttackAbility::MonitorLandingProgress, 0.02f, true);
}

void UJumpAttackAbility::StopMonitoringLanding()
{
	GetWorld()->GetTimerManager().ClearTimer(TickTimerHandle);
}

void UJumpAttackAbility::MonitorLandingProgress()
{
	if (ShouldTriggerLandingDynamic(PredictionTime))
	{
		// Пора! Вызываем событие в Блюпринт
		OnLandingPredicted();
        
		// Останавливаем мониторинг
		StopMonitoringLanding();
	}
    
	// Дополнительная проверка: если мы уже не в воздухе, тоже стоп
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (Character && !Character->GetCharacterMovement()->IsFalling())
	{
		OnLandingPredicted(); // На всякий случай триггерим приземление
		StopMonitoringLanding();
	}
}

float UJumpAttackAbility::GetDynamicPredictDistance(float InPredictionTime) const
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!Character || !Character->GetCharacterMovement()) return 150.f;
	
	float VerticalVelocity = FMath::Abs(Character->GetCharacterMovement()->Velocity.Z);
    
	// Рассчитываем дистанцию. Минимум 100 единиц, чтобы не пропустить землю на низкой скорости.
	return FMath::Max(100.f, VerticalVelocity * InPredictionTime);
}

bool UJumpAttackAbility::ShouldTriggerLandingDynamic(float InPredictionTime)
{
	float DistanceToGround = GetDistanceToGround();
    
	// Если земля не найдена или слишком далеко
	if (DistanceToGround < 0.f || DistanceToGround >= 2000.f) return false;

	float DynamicThreshold = GetDynamicPredictDistance(InPredictionTime);

	return DistanceToGround <= DynamicThreshold;
}
