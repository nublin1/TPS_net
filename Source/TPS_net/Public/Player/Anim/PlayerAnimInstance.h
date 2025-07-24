// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Library/AnimationStructLibrary.h"
#include "PlayerAnimInstance.generated.h"

struct FGameplayTag;
class UCharacterMovementComponent;
class UMovementComponent;
class UStateMachineComponent;
class AMasterWeapon;
class APlayerCharacter;
class UWeaponSystemComponent;
/**
 * 
 */
UCLASS()
class TPS_NET_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	UPROPERTY(BlueprintReadWrite)
	bool IsShootingWeapon;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector ReloadPosition;

	
	UPROPERTY(BlueprintReadWrite)
	bool IsInitilize = false;

	/** Anim Graph - Components */
	UPROPERTY(BlueprintReadWrite, Category="References")
	TObjectPtr<UWeaponSystemComponent> WeaponSysComponent;
	UPROPERTY(BlueprintReadWrite, Category="References")
	TObjectPtr<UStateMachineComponent> StateMachine_Movement;
	UPROPERTY(BlueprintReadWrite, Category="References")
	TObjectPtr<UStateMachineComponent> StateMachine_Aiming;
	UPROPERTY(BlueprintReadWrite, Category="References")
	TObjectPtr<UCharacterMovementComponent> ChMovementComponent;
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Character,  BlueprintReadWrite, Category="References")
	TObjectPtr<APlayerCharacter> Character;

	/** Anim Graph - In Air */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Anim Graph - In Air")
	FAnimGraphInAir InAir;
	
	/** Character Information */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Character Information", Meta = (
		ShowOnlyInnerProperties))
	FAnimCharacterInformation CharacterInformation;
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
	bool IsHoldWeapon;

	/** Anim Graph - Layer Blending */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Graph - Layer Blending")
	FAnimGraphLayerBlending LayerBlendingValues;

	/** Anim Graph - Aiming Values */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Aiming Values")
	FAnimGraphAimingValues AimingValues;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FTransform LeftHandIKTransform = FTransform();

	/** Configuration */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration|Main Configuration")
	FAnimConfiguration Config;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	
	UFUNCTION()
	virtual void NativeInitializeAnimation() override;
	UFUNCTION()
	virtual void NativeBeginPlay() override;
	UFUNCTION()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable)
	virtual void SighUp();

	UFUNCTION()
	virtual void SetIKHands();
	UFUNCTION()
	virtual void UpdateLayerValues();
	UFUNCTION()
	virtual void UpdateAimingValues(float DeltaSeconds);

	UFUNCTION()
	virtual void WeaponStateChanged(AActor* Actor, const FGameplayTag& NewStateTag);
	UFUNCTION()
	virtual void AimingStateChanged(AActor* Actor, const FGameplayTag& NewStateTag);
	
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void UpdateWeaponHoldPose();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void CleanWeaponData(AMasterWeapon* MasterWeapon);
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void UpdateWeaponData(AMasterWeapon* newMasterWeapon);

	UFUNCTION()
	void OnRep_Character();

	UFUNCTION()
	void OnJumped();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
};
