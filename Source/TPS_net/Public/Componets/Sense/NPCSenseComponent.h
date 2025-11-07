// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCSenseComponent.generated.h"


struct FSenseData;

UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UNPCSenseComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorSensed, AActor*, SensedActor);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorOutOfSense, AActor*, LostActor);

public:
	UNPCSenseComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Sense")
	bool bIsSensingEnabled = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sense|Debug")
	bool bDrawDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sense")
	FName ViewComponentTag = TEXT("ViewMesh");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sense")
	TObjectPtr<USceneComponent> ViewComponent = nullptr;
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

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> DetectedActors;
	
	FTimerHandle TimerHandle_Sense;

	//====================================================================
	// FUNCTIONS
	//====================================================================	
	void PerformSenseCheck();

	bool IsInViewCone(AActor* OtherActor) const;
	bool HasLineOfSight(AActor* OtherActor) const;

	FVector GetViewLocation() const;
	FVector GetViewForward() const;

public:
	UPROPERTY(BlueprintAssignable, Category="Sense")
	FOnActorSensed OnActorSensed;
	UPROPERTY(BlueprintAssignable, Category="Sense")
	FOnActorOutOfSense OnActorOutOfSense;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual void InitSense(FSenseData SenseData);
	
	UFUNCTION(blueprintCallable, Category="Sense")
	void SetSensingEnabled(bool bEnable);
};
