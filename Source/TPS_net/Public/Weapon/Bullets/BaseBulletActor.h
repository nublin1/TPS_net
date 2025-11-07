// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBulletActor.generated.h"

class UAmmoBase;

UENUM(BlueprintType)
enum class EBulletFlightMode : uint8
{
	/**  */
	Physical UMETA(DisplayName="Physical"),

	/** Простая баллистическая дуга */
	Parabolic UMETA(DisplayName="Parabolic"),
};

UCLASS()
class TPS_NET_API ABaseBulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseBulletActor();

protected:	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Destroy();

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBulletFlightMode BulletFlightMode = EBulletFlightMode::Physical;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAmmoBase> SelectedAmmoData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	TArray<TObjectPtr<AActor>> ActorsToIgnore;

	UFUNCTION(BlueprintNativeEvent)
	void InitBullet();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	TEnumAsByte<ETraceTypeQuery> CollisionChannel = ETraceTypeQuery::TraceTypeQuery1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	FHitResult Hit;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpawnDecalAfterHit = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool SpawnEffectOnGroundAfterHit = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> SpawnOnGroundEffect = nullptr;

	//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoAim = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation = FVector::Zero();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetLocation = FVector::Zero();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAngle = 85.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRange = 10000.0f;
};
