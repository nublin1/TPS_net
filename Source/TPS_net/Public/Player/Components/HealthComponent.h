// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKilledSignature, AActor*, KilledActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, CurrentHealth);

#pragma endregion

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnKilledSignature OnKilledDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChangedDelegate;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UHealthComponent();

	UFUNCTION(BlueprintCallable )
	virtual void TakeDamage(float DamageAmount);
	UFUNCTION(Server, Unreliable)
	virtual void ServerTakeDamage(float DamageAmount);
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticastTakeDamage(float DamageAmount);

	// Getters
	virtual float GetHealth() const {return Health;}
	virtual float GetMaxHealth() const {return MaxHealth;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool bIsGodMode = false;
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Health, BlueprintReadWrite)
	float Health = 100.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.0f;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;

	UFUNCTION()
	void OnRep_Health() const;
};
