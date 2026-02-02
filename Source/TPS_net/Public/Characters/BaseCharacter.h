// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/FactionSystem/FactionOwnerInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Data/Characters/CharacterStructs.h"
#include "BaseCharacter.generated.h"

class ULadderClimbingComponent;
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
	virtual void PostInitializeComponents() override;
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

	// ASC
	UFUNCTION(BlueprintCallable, Category="AbilitySystem" )
	TArray<FGameplayAbilitySpecHandle> GrantAbilities (TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);
	UFUNCTION(BlueprintCallable, Category="AbilitySystem" )
	void RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove);
	UFUNCTION(BlueprintCallable, Category="AbilitySystem" )
	void SendAbilitiesChangedEvent();

	//
	UFUNCTION(BlueprintCallable)
	bool IsStateTransitionAllowed(FGameplayTag NewState);

	//
	UFUNCTION()
	virtual UStateMachineComponent* GetActiveStateCharacter() {return ActiveStateCharacter;}
	UFUNCTION()
	virtual UStateMachineComponent* GetStateMachine_Movement() {return StateMachine_Movement;}
	UFUNCTION()
	virtual FName GetFactionName_Implementation() const override { return FactionName; }

	virtual USkeletalMeshComponent* GetSkeletalMeshComponent() {return SkeletalMeshComponent;}

	virtual ULadderClimbingComponent* GetLadderClimbingComponent() const {return LadderClimbingComponent;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Components Clasees
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ULadderClimbingComponent> LadderClimbingComponentClass = nullptr;
	
	// Components
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStateMachineComponent> ActiveStateCharacter;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Aiming;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<ULadderClimbingComponent> LadderClimbingComponent;

	//ASC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;

	/** MovementState tags */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MovementState")
	//FGameplayTag SavedMovementStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MovementState")
	FGameplayTag IdleMovementStateTag;

	/** CharacterState tags */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag SavedActiveStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag AliveStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag DeadStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag DownedStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag RagdollStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag RevivingStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag RagdollEnterStateTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterState")
	FGameplayTag RagdollExitStateTag;
	

	/** Essential Information */
	UPROPERTY(Replicated, BlueprintReadWrite)
	FVector2D MovementVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMoving = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsGrounded = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bWasFalling = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector SavedVelocityAfterFalling = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EFallImpactType FallImpactType = EFallImpactType::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FallingHeavyImpactSpeed = -750.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FallingRagdollImpactSpeed = -1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* FallingHardImpactMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Fall Damage")
	float MinFallDamageSpeed = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Fall Damage")
	float MaxFallDamageSpeed = 2500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Fall Damage")
	float MaxFallDamage = 100.0f;
	

	/** Ragdoll Information */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RagdollInfo")
	bool bRagdollFaceUp = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RagdollInfo")
	bool bRagdollOnGround = true;
	UPROPERTY()
	bool bWasRagdollOnGround = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RagdollInfo")
	FVector TargetRagdollLocation = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RagdollInfo")
	FRotator TargetRagdollRotator = FRotator::ZeroRotator;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RagdollInfo")
	FVector LastRagdollVilocity = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RagdollInfo")
	TObjectPtr<UAnimMontage> AnimMontage_RagdollStandUp_FaceUp = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RagdollInfo")
	TObjectPtr<UAnimMontage> AnimMontage_RagdollStandUp_FaceDown = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ragdoll")
	float RagdollStopSpeed = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ragdoll|State")
	float RagdollMinDuration = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ragdoll/State")
	float RagdollMinTimeOnGround = 0.4f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RagdollInfo")
	float RagdollStartTime = -1.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RagdollInfo")
	float RagdollGroundedStartTime = -1.0f;

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

	//
	UFUNCTION()
	void OnAbilityEnded(const FAbilityEndedData& EndedData);
	UFUNCTION(BlueprintImplementableEvent)
	void AbilityEndedInfo(FAbilityEndedDataBlueprintWrapper EndedAbilityData);

	//
	UFUNCTION(BlueprintCallable)
	void UpdateActorDuringRagdoll();

	//
	UFUNCTION(BlueprintCallable)
	void ApplyKnockback(FVector RadialImpactNormal, const float KnockbackStrength);

	UFUNCTION(BlueprintCallable)
	void RagdollEnd();
	void OnRagdollStandUpMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION(BlueprintCallable)
	void ClearFallImpactData();
	UFUNCTION(BlueprintCallable, Category="Fall Impact")
	EFallImpactType CalculateFallImpact(const FVector& Velocity) const;

	UFUNCTION(BlueprintCallable)
	float CalculateFallDamage(const FVector& Velocity) const;
};
