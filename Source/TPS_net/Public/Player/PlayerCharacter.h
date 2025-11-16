// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStructsLibrary.h"
#include "Characters/BaseCharacter.h"

#include "Interfaces/IHealthInterface.h"
#include "Interfaces/WeaponSystemInterface.h"
#include "Library/AnimationStructLibrary.h"

#include "PlayerCharacter.generated.h"

class UCameraComponent;
class ACoverPoint_Player;
class ULadderClimbingComponent;
struct FGameplayTag;
class UBoxComponent;
class UStateMachineComponent;

UCLASS()
class TPS_NET_API APlayerCharacter : public ABaseCharacter, public IIHealthInterface
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpedSignature);

public:
	APlayerCharacter();

protected:
	virtual void PostInitProperties() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

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
	// Getters
	UFUNCTION()
	virtual UCameraComponent* GetCamera() {return FollowCamera;}
	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const override;
	UFUNCTION()
	virtual UWeaponSystemComponent* GetWeaponSystemComponent() const {return WeaponSystemComponent;}
	
	UFUNCTION()
	virtual UStateMachineComponent* GetStateMachine_Aiming() {return StateMachine_Aiming;}
	UFUNCTION()
	virtual UStateMachineComponent* GetActiveStateCharacter() {return ActiveStateCharacter;}
	virtual ULadderClimbingComponent* GetLadderClimbingComponent() const {return LadderClimbingComponent;}

	FTimerHandle GetShootingPoseTransitionTimer() const {return ShootingPoseTransitionTimer;}

	/** Essential Information Getters/Setters */
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	FVector2D GetMovementVector() const { return MovementVector; }
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	bool GetIsMoving() const { return IsMoving; }
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	float GetSpeed() const { return Speed; }
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	FRotator GetAimingRotation() const {return AimingRotation;}

	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	FAnimGraphAimingValues GetAimingValues() const { return AimingValues; }
	UFUNCTION(BlueprintGetter, Category = "Essential Information")
	FAnimGraphCoverValues GetCoverValues() const { return AnimCoverValues; }

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUseDesiredRotation = false;

	/** Cover System */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Refs")
	TObjectPtr<ACoverPoint_Player> CurrentCoverPoint_Player = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	bool bIsInsideCoverArea = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	bool bCoverAimRightAvailible = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	bool bCoverAimLeftAvailible = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	bool bIsInEndAreaRight = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	bool bIsInEndAreaLeft = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	EStandCrouchCoverPose CoverPose = EStandCrouchCoverPose::Standing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Refs")
	TObjectPtr<UStaticMeshComponent> CoverBackWallMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Settings")
	float CoverEnterAngleArea = 95.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Settings")
	float CapsuleRadiusInCover = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	bool bCharacterFacingToCoverRight = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover System|Data")
	bool bCharacterMovingInCoverRight = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Cover Values")
	FAnimGraphCoverValues AnimCoverValues;
	

	/** Aiming Values */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aiming Values")
	FAnimGraphAimingValues AimingValues;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration|Anim")
	FAnimConfiguration Config;

	// Components Clasees
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ULadderClimbingComponent> LadderClimbingComponentClass = nullptr;
	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Aiming;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* ActiveStateCharacter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<ULadderClimbingComponent> LadderClimbingComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<UWeaponSystemComponent> WeaponSystemComponentClass;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponSystemComponent> WeaponSystemComponent;

	//Timers
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FTimerHandle CollisionOffTimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle HipFireCooldownTimeHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HipFireToIdleTransitionTime = 3.3f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTimerHandle ShootingPoseTransitionTimer;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	void SetEssentialValues(float DeltaTime);
	void UpdateCoverValues(float DeltaTime);
	void UpdateAimingValues(float DeltaTime);

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

	// MovementSpeed
	virtual void ChangeMaxMoveSpeed(float NewMaxSpeed) override;
	void ServerSetSpeed_Implementation(float NewMaxSpeed);
	void MulticastSetSpeed_Implementation(float NewMaxSpeed);

	//
	UFUNCTION(BlueprintCallable)
	bool IsStateTransitionAllowed(FGameplayTag NewState);
	
	//
	UFUNCTION(BlueprintCallable)
	void ShortCollisionOff(UBoxComponent* TargetCollision);

	UFUNCTION()
	void AnimStateChanged(FName PrevState, FName CurrentState);

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
};
