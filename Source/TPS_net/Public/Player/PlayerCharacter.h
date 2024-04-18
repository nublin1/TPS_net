// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UStateMachineComponent;

UCLASS()
class TPS_NET_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// Properties
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite )
	bool IsAiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGrounded;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraInterpolationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FVector CurrentCameraLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FVector DesiredCameraLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DefaultCameraLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AimingCameraPosition;

	UPROPERTY(BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Movemant;
	UPROPERTY(BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Aiming;
	
	//Functions
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
};
