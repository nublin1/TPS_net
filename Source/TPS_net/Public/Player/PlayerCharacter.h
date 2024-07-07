// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ClimbableInterface.h"
#include "PlayerCharacter.generated.h"

class UBoxComponent;
class UStateMachineComponent;

UCLASS()
class TPS_NET_API APlayerCharacter : public ACharacter, public IClimbableInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
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

	UPROPERTY(BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Movemant;
	UPROPERTY(BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Aiming;

	//Ladder
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* LadderTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUpLadderEntry;

	//Timers
	UPROPERTY()
	FTimerHandle CollisionOffTimerHandle;
	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void StartClimbing() override;	
	
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
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
