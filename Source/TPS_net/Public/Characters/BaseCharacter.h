// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/FactionSystem/FactionOwnerInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "BaseCharacter.generated.h"

class UCharacterDataAsset;
class UBaseAttributeSet;
class UStateMachineComponent;

UCLASS()
class TPS_NET_API ABaseCharacter : public ACharacter, public IFactionOwnerInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}

	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//ASC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UBaseAttributeSet> BaseAttributes;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual void InitCharacterData();
	UFUNCTION(BlueprintNativeEvent)
	void InitSetBaseCharacterStats();
	
	virtual UStateMachineComponent* GetStateMachine_Movement() {return StateMachine_Movement;}
	UFUNCTION()
	virtual FName GetFactionName_Implementation() const override { return FactionName; }

	virtual USkeletalMeshComponent* GetSkeletalMeshComponent() {return SkeletalMeshComponent;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Components
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	//ASC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;

	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UCharacterDataAsset> CharacterData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data|Faction")
	FName FactionName = "Neutral";

	//Dying
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USoundBase> DyingSound;
	UPROPERTY()
	FTimerHandle DeadHandle;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	// MovementSpeed
	UFUNCTION(BlueprintCallable)
	virtual void ChangeMaxMoveSpeed(float NewMaxSpeed);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	virtual void ServerSetSpeed(float NewMaxSpeed);
	UFUNCTION(NetMulticast, Unreliable)
	virtual void MulticastSetSpeed(float NewMaxSpeed);

	//
	UFUNCTION(BlueprintCallable)
	void NPCDead(AActor* KilledActor, AController* EventInstigator);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void Server_NPCDead(AActor* KilledActor);
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_NPCDead(AActor* KilledActor);
	
};
