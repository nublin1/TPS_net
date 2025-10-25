// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHealthInterface.h"
#include "NPC/Inrfaces/ZombieCombatInterface.h"
#include "NPCZombie.generated.h"

UCLASS()
class TPS_NET_API ANPCZombie : public ABaseCharacter, public IIHealthInterface, public IZombieCombatInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ANPCZombie();

protected:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USoundBase> DyingSound;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	// MovementSpeed
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
	UFUNCTION(BlueprintCallable)
	void NPCDead(AActor* KilledActor, AController* EventInstigator);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
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
