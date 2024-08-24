// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHealthInterface.h"
#include "NPCCharacter.generated.h"

UCLASS()
class TPS_NET_API ANPCCharacter : public ACharacter, public IIHealthInterface
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
	// Sets default values for this character's properties
	ANPCCharacter();

	UFUNCTION()
	virtual void TakeDamage(float DamageAmount) override;

	UFUNCTION()
	virtual FOnKilledSignature& GetOnKilledSignature() override {return OnKilledDelegate;}
	
	UFUNCTION()
	virtual float GetHealth() const override { return Health; }
	UFUNCTION()
	virtual float GetMaxHealth() const override { return MaxHealth; }

protected:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
