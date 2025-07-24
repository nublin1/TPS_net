// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ClimbableInterface.h"
#include "Interfaces/IHealthInterface.h"
#include "Interfaces/WeaponSystemInterface.h"
#include "PlayerCharacter.generated.h"

struct FGameplayTag;
class UBoxComponent;
class UStateMachineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpedSignature);

UCLASS()
class TPS_NET_API APlayerCharacter : public ACharacter, public IIHealthInterface, public IWeaponSystemInterface
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	/** Input */
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnJumpedSignature OnJumpedDelegate;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	APlayerCharacter();

	// Getters
	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const override;
	UFUNCTION()
	virtual UWeaponSystemComponent* GetWeaponSystemComponent() const override {return WeaponSystemComponent;}
	UFUNCTION()
	virtual UStateMachineComponent* GetStateMachine_Movement() {return StateMachine_Movement;}
	UFUNCTION()
	virtual UStateMachineComponent* GetStateMachine_Aiming() {return StateMachine_Aiming;}
	UFUNCTION()
	virtual UStateMachineComponent* GetActiveStateCharacter() {return ActiveStateCharacter;}

	/** Essential Information Getters/Setters */
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	FVector2D GetMovementVector() const { return MovementVector; }
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	bool GetIsMoving() const { return IsMoving; }
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	float GetSpeed() const { return Speed; }
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	FRotator GetAimingRotation() const {return AimingRotation;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	/** Essential Information */
	UPROPERTY(Replicated, BlueprintReadWrite)
	FVector2D MovementVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGrounded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSprintingButtonHeld = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAimingButtonHeld = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Essential Information")
	float Speed = 0.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	float TargetMaxWalkSpeed = 600.0f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraInterpolationSpeed;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FVector CurrentCameraLocation;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FVector DesiredCameraLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DefaultCameraLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AimingCameraPosition;
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Essential Information")
	FRotator ReplicatedControlRotation = FRotator::ZeroRotator;
	/* Smooth out aiming by interping control rotation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator AimingRotation = FRotator::ZeroRotator;

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Movement;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Aiming;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* ActiveStateCharacter;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<UWeaponSystemComponent> WeaponSystemComponentClass;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponSystemComponent> WeaponSystemComponent;
	
	//Ladder
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* LadderTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUpLadderEntry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder")
	bool LadderIsNextLeftArm;

	//Timers
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FTimerHandle CollisionOffTimerHandle;
	
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle HipFireCooldownTimeHandle;
	UPROPERTY(BlueprintReadWrite)
	float HipFireToIdleTransitionTime;
	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void PostInitializeComponents() override;

	void SetEssentialValues(float DeltaTime);

	/** On Jumped*/
	UFUNCTION(BlueprintCallable, Category = "Character States")
	void EventOnJumped();
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Character States")
	void Multicast_OnJumped();

	virtual void OnJumped_Implementation() override;
	
	// Deadth
	UFUNCTION()
	void OnHealthDepleted(AActor* Actor, AController* EventInstigator);
	UFUNCTION(Server, Unreliable)
	void ServerOnHealthDepleted();
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticastOnHealthDepleted();

	// MovemantSpeed
	UFUNCTION(BlueprintCallable)
	void ChangeMaxMoveSpeed(float NewMaxSpeed);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void ServerSetSpeed(float NewMaxSpeed);
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSetSpeed(float NewMaxSpeed);
	
	// Ladder climbing
	UFUNCTION(BlueprintCallable)
	virtual void StartClimbing();	
	UFUNCTION(Server, Unreliable, WithValidation, BlueprintCallable)
	void ServerStartClimbing(USceneComponent* TargetMoveToComponent);
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastStartClimbing(USceneComponent* TargetMoveToComponent);

	//
	UFUNCTION(BlueprintCallable)
	bool IsStateTransitionAllowed(FGameplayTag NewState);

	
	//
	UFUNCTION(BlueprintCallable)
	void ShortCollisionOff(UBoxComponent* TargetCollision);


public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
};
