// Nublin Studio 2026 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Library/AnimationStructLibrary.h"
#include "PlayerAnimInstance.generated.h"

enum class EWeaponType : uint8;
class ABaseWeapon;
class ULadderClimbingComponent;
struct FGameplayTag;
class UCharacterMovementComponent;
class UMovementComponent;
class UStateMachineComponent;
class AMasterWeaponRanged;
class APlayerCharacter;
class UWeaponSystemComponent;
/**
 * 
 */
UCLASS()
class TPS_NET_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewAnimState, FName, PrevState, FName, CurrentState);

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FNewAnimState NewAnimState;
	
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
	UPROPERTY(BlueprintReadWrite,Category="References")
	TObjectPtr<ULadderClimbingComponent> LadderClimbingComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="References")
	TObjectPtr<UStateMachineComponent> CharacterActiveState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="References")
	TObjectPtr<UWeaponSystemComponent> WeaponSysComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="References")
	TObjectPtr<UStateMachineComponent> StateMachine_Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="References")
	TObjectPtr<UStateMachineComponent> StateMachine_Aiming;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="References")
	TObjectPtr<UCharacterMovementComponent> ChMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="References")
	TObjectPtr<APlayerCharacter> Character;

	/** Anim Graph - In Air */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Anim Graph - In Air")
	FAnimGraphInAir InAir;
	
	/** Character Information */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Character Information", Meta = (
		ShowOnlyInnerProperties))
	FAnimCharacterInformation CharacterInformation;	

	/** Anim Graph - Layer Blending */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Graph - Layer Blending")
	FAnimGraphLayerBlending CurrentLayerBlendingValues;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Graph - Layer Blending")
	FAnimGraphLayerBlending WeaponLayerBlendingValues;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anim Graph - Layer Blending")
	bool bIsNeedOverBlendOverlayLayer = false;
	
	/** Weapon Information */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsHoldWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType WeaponType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> BlendSpaceRegular;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> BlendSpaceAiming;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bAimOffsetIsValid = false;

	/** Anim Graph - Aiming Values */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Aiming Values")
	FAnimGraphAimingValues AimingValues;

	/** Anim Graph - Cover Values */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Cober Values")
	FAnimGraphCoverValues AnimCoverValues;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FTransform LeftHandIKTransform = FTransform();
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FTransform RightHandIKTransform = FTransform();
	
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
	virtual void CleanWeaponData(ABaseWeapon* MasterWeapon);
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void UpdateWeaponData(ABaseWeapon* newMasterWeapon);

	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void UpdateOverrideData();

	UFUNCTION()
	void OnJumped();

	UFUNCTION()
	void ChangedState();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName PreviousState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool StateWasChanged = false;
};
