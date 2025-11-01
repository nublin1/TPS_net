// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIAttackComponent.generated.h"


class UBoxComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API UAIAttackComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartAttackSignature);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndAttackSignature);
#pragma endregion

public:
	UAIAttackComponent();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEndAttackSignature EndAttackDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStartAttackSignature StartAttackDelegate;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(Server, Reliable)
	void Server_HitDetect();
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerClearAlreadyHitTargets();

	UFUNCTION()
	void SetTargetActor (AActor* NewTargetActor);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Attack")
	FVector SocketLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	FName AttackSocketName = FName("hand_r");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float TraceRadius = 45.0f;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> TargetActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ReadyToAttack = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackCooldown = 2.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 115.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> MontageAttack;

	//
	UPROPERTY()
	FTimerHandle TimerHandleAttackPeriod;

	UPROPERTY(BlueprintReadOnly)
	TMap<AActor*, bool> AlreadyHitTargets;

	UPROPERTY(EditAnywhere)
	bool IsDebug = false;

	//Data
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAnimInstance> AnimInstance = nullptr;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	bool CanStartAttack();
	UFUNCTION(blueprintCallable)
	void SimpleMeleeAttack();
	UFUNCTION(blueprintCallable)
	void RangedAttack();
	UFUNCTION()
	void SimpleAttackCompleted(UAnimMontage* Montage, bool bInterrupted);
	
	UFUNCTION(BlueprintCallable)
	void RequestHitDetect();
	UFUNCTION()
	bool HitDetect();	
	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(AActor* HitActor);
	UFUNCTION(BlueprintCallable)
	void ClearAlreadyHitTargets();
	UFUNCTION()
	bool InRangeToAttack() const;
	UFUNCTION(BlueprintCallable)
	void RotateToTarget();

private:

};
