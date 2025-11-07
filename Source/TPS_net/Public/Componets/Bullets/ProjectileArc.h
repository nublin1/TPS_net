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
	bool bAutoCalculateAngle = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Settings")
	float Gravity = 980.f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Settings")
	float LifeTime = 10.0f;

	//Data
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	FVector PreviousLocation;
	
	FCollisionQueryParams Params;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	TEnumAsByte<ETraceTypeQuery> CollisionChannel = ETraceTypeQuery::TraceTypeQuery1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	TArray<TObjectPtr<AActor>> ActorsToIgnore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult OutHit;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual void HitDetected();

protected:
	bool IsInitialized = false;
	FVector StartLocation;
	FVector TargetLocation;

	/** Нормализованное расстояние (0..1) от минимума до MaxRange */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NormalizedDistance = 0.f;
	/** Угол броска (в радианах) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LaunchAngleRad = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	/** Скорость движения вдоль траектории (см/с) */
	float MoveSpeed = 1500.f;
	/** Текущее "время" движения по траектории (вдоль кривой) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TravelT = 0.f;
	/** Общая длительность полёта в секундах */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TotalFlightTime = 1.f;
};
