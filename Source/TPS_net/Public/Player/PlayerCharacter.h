// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ClimbableInterface.h"
#include "Interfaces/IHealthInterface.h"
#include "Interfaces/WeaponSystemInterface.h"
#include "PlayerCharacter.generated.h"

class UBoxComponent;
class UStateMachineComponent;

UCLASS()
class TPS_NET_API APlayerCharacter : public ACharacter, public IIHealthInterface, public IWeaponSystemInterface
{
	GENERATED_BODY()

public:
	
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
	virtual UStateMachineComponent* GetStateMachine_Aiming() {return StateMachine_Aiming;}
	UFUNCTION()
	virtual UStateMachineComponent* GetActiveStateCharacter() {return ActiveStateCharacter;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(Replicated, BlueprintReadWrite)
	FVector2D MovementVector;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite )
	bool IsAiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGrounded;
	
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

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(Replicated, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Movement;
	UPROPERTY(Replicated, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Aiming;
	UPROPERTY(Replicated, BlueprintReadWrite)
	UStateMachineComponent* ActiveStateCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWeaponSystemComponent> WeaponSystemComponentClass;
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
	UPROPERTY()
	FTimerHandle CollisionOffTimerHandle;
	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void PostInitializeComponents() override;

	
	// deadth
	UFUNCTION()
	void OnHealthDepleted(AActor* Actor);
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
	void ShortCollisionOff(UBoxComponent* TargetCollision);


public:	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
};
