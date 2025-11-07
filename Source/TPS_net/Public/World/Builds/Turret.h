// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UNPCSenseComponent;

UCLASS()
class TPS_NET_API ATurret : public AActor
{
	GENERATED_BODY()

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetAcquired, AActor*, TargetActor);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetLost, AActor*, LastTargetActor);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetAligned);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetAlignedLost);
#pragma endregion

public:
	ATurret();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	// Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTargetAcquired OnTargetAcquired;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTargetLost OnTargetLost;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTargetAligned OnTargetAligned;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTargetAlignedLost OnTargetAlignedLost;
	
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float RotationRate = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings | Limits")
	float MaxYawLimit = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Targeting")
	float AimThreshold = 4.0f; // В градусах

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	FName RotatingComponentTag = TEXT("RotatingMesh");
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	USceneComponent* RotatingMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	float RotationDirection = 1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	float StartYaw = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<AActor> CurrentTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	bool bIsAimed = false;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	void RotationToTarget(float DeltaTime);
	UFUNCTION()
	void IdleRotation(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void PerformAttack();
};
