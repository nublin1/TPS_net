// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Characters/CharacterStructs.h"
#include "AIAttackComponent.generated.h"


class UWeaponSystemComponent;
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
	UFUNCTION()
	void InitAttackComponent();

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

	UPROPERTY(EditAnywhere)
	bool IsDebug = false;

	//Refs
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponSystemComponent> WeaponSystemComponentRef;
	

	//====================================================================
	// FUNCTIONS
	//===================================================================	
	UFUNCTION()
	void AttackCompleted(UAnimMontage* Montage, bool bInterrupted);
	
	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(AActor* HitActor);
	UFUNCTION()
	bool InRangeToAttack() const;
	UFUNCTION(BlueprintCallable)
	void RotateToTarget();

private:

};
