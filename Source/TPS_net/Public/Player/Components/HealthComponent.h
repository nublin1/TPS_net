// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKilledSignature, AActor*, KilledActor);

#pragma endregion

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintAssignable)
	FOnKilledSignature OnKilledDelegate;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UHealthComponent();
	UHealthComponent(float Health, float MaxHealth);

	UFUNCTION(BlueprintCallable )
	virtual void TakeDamage(float DamageAmount);

	// Getters

	virtual float GetHealth() const {return Health;}
	virtual float GetMaxHealth() const {return MaxHealth;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	float Health;
	UPROPERTY()
	float MaxHealth;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;
};
