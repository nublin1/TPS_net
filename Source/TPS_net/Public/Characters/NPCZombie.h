// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHealthInterface.h"
#include "NPC/Inrfaces/AIAttackInterface.h"
#include "NPCZombie.generated.h"

UCLASS()
class TPS_NET_API ANPCZombie : public ABaseCharacter, public IIHealthInterface, public IAIAttackInterface
{
	GENERATED_BODY()
public:
	ANPCZombie();

protected:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const override;
	UFUNCTION()
	virtual class UAIAttackComponent* GetAIAttackComponent() const override {return AIAttackComponent;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAIAttackComponent> AIAttackComponent;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Transformation")
	float SprintSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ReadyToAttack = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USoundBase> DyingSound;

	//Timers
	UPROPERTY()
	FTimerHandle UnusedHandle;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	
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
	
	
};
