// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHealthInterface.h"
#include "NPC/Inrfaces/ZombieCombatInterface.h"
#include "NPCZombie.generated.h"

UCLASS()
class TPS_NET_API ANPCZombie : public ACharacter, public IIHealthInterface, public IZombieCombatInterface
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	// Sets default values for this character's properties
	ANPCZombie();

	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const override;
	UFUNCTION()
	virtual class UZombieCombatComponent* GetZombieCombatComponent() const override {return ZombieCombatComponent;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UZombieCombatComponent* ZombieCombatComponent;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void RerunConstructionScripts() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
