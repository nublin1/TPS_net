// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieCombatComponent.generated.h"


class UBoxComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API UZombieCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UZombieCombatComponent();

	UFUNCTION(Server, Reliable)
	void Server_HitDetect();
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerClearAlreadyHitTargets();

	//Getters
	

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AgroRange = 500;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AgroOutRange = 750;

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
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool RequestHitDetect();
	UFUNCTION()
	bool HitDetect();	
	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(AActor* HitActor);
	UFUNCTION(BlueprintCallable)
	void ClearAlreadyHitTargets();
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

};
