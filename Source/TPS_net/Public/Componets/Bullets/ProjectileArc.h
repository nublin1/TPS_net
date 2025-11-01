// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileArc.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UProjectileArc : public UActorComponent
{
	GENERATED_BODY()

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitSignature, const FHitResult&, HitResult);
#pragma endregion

public:
	UProjectileArc();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FHitSignature HitResultDelegate;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void Launch(const FVector& Start, const FVector& Target, float MaxRange, float MaxAngle = 45.0f);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Settings")
	float Gravity = 980.f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Settings")
	float LifeTime = 10.0f;

	//Data
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	FVector PreviousLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_GameTraceChannel1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult OutHit;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual void HitDetected();

private:
	bool bLaunched = false;
	FVector StartLocation;
	FVector TargetLocation;

	/** Нормализованное расстояние (0..1) от минимума до MaxRange */
	float NormalizedDistance = 0.f;

	/** Угол броска (в радианах) */
	float LaunchAngleRad = 0.f;

	/** Скорость движения вдоль траектории (см/с) */
	float MoveSpeed = 1000.f;

	/** Текущее "время" движения по траектории (вдоль кривой) */
	float TravelT = 0.f;

	/** Общая длительность полёта в секундах */
	float TotalFlightTime = 1.f;
};
