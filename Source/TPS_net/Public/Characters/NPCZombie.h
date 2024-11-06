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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UZombieCombatComponent> ZombieCombatComponent;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Transformation")
	float SprintSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ReadyToAttack = true;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void RerunConstructionScripts() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	// MovemantSpeed
	UFUNCTION(BlueprintCallable)
	void ChangeMaxMoveSpeed(float NewMaxSpeed);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void ServerSetSpeed(float NewMaxSpeed);
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSetSpeed(float NewMaxSpeed);

	// Attack
	UFUNCTION(BlueprintCallable)
	void SimpleAttack(UAnimMontage* MontageToPlay);

	//
	UFUNCTION()
	void SimpleAttackCompleted(UAnimMontage* Montage, bool bInterrupted);

	//
	UFUNCTION()
	void NPCDead(AActor* KilledActor, AController* EventInstigator);
	UFUNCTION(Server, Unreliable)
	void Server_NPCDead(AActor* KilledActor);
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_NPCDead(AActor* KilledActor);
	

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
};
