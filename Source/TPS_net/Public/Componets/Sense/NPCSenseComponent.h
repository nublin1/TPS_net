// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCSenseComponent.generated.h"


UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UNPCSenseComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorSensed, AActor*, SensedActor);

public:
	UNPCSenseComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Sense")
	bool bIsSensingEnabled = true;

	UPROPERTY(EditAnywhere, Category="Sense")
	float SenseRadius = 1000.f;
	UPROPERTY(EditAnywhere, Category="Sense")
	float VisionAngle = 90.f;
	UPROPERTY(EditAnywhere, Category="Sense")
	float UpdateInterval = 0.5f;

	UPROPERTY(EditAnywhere, Category="Sense")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, Category="Sense")
	TArray<TSubclassOf<AActor>> DetectableClasses;

	FTimerHandle TimerHandle_Sense;

	void PerformSenseCheck();

	bool IsInViewCone(AActor* OtherActor) const;
	bool HasLineOfSight(AActor* OtherActor) const;

public:
	UPROPERTY(BlueprintAssignable, Category="Sense")
	FOnActorSensed OnActorSensed;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(blueprintCallable, Category="Sense")
	void SetSensingEnabled(bool bEnable);
};
