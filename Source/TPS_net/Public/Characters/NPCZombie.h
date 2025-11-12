// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AI/Al_Helper.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHealthInterface.h"
#include "NPC/Inrfaces/AIAttackInterface.h"
#include "NPCZombie.generated.h"

class UWeaponSystemComponent;
class UNPCSenseComponent;

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
	virtual void InitCharacterData() override;
	
	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const override;
	UFUNCTION()
	virtual class UAIAttackComponent* GetAIAttackComponent() const override {return AIAttackComponent;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStateMachineComponent> BehavorState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAIAttackComponent> AIAttackComponent;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNPCSenseComponent> SenseComponent;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Transformation")
	float SprintSpeed = 600.0f;
	

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> ChaseTarget = nullptr;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	// Attack
	UFUNCTION()
	void OnAttack();
	UFUNCTION()
	void OnAttackCompleted();
	
	//
	UFUNCTION()
	void OnActorSensed(AActor* SensedActor);

};
