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

public:
	UAIAttackComponent();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(Server, Reliable)
	void Server_HitDetect();
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerClearAlreadyHitTargets();

	//Getters
	

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AgroRange = 500;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AgroOutRange = 750;*/

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Attack")
	FVector SocketLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	FName AttackSocketName = FName("hand_r");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float TraceRadius = 45.0f;

	UPROPERTY(BlueprintReadOnly)
	TMap<AActor*, bool> AlreadyHitTargets;

	UPROPERTY(EditAnywhere)
	bool IsDebug = false;

	//Anim
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	

	UFUNCTION(BlueprintCallable)
	bool RequestHitDetect();
	UFUNCTION()
	bool HitDetect();	
	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(AActor* HitActor);
	UFUNCTION(BlueprintCallable)
	void ClearAlreadyHitTargets();

private:

};
