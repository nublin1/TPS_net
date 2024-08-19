// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsHoldWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector LeftHandPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector ReloadPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsLeftHandNeeded = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsUseHoldWeaponPose = false;

	//
	UPROPERTY(BlueprintReadWrite, Category="References")
	TObjectPtr<UWeaponSystemComponent> WeaponSysComponent;
	UPROPERTY(BlueprintReadWrite, Category="References")
	TObjectPtr<APlayerCharacter> Character;

	UPROPERTY(BlueprintReadWrite)
	bool IsInitilize = false;

	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	
	UFUNCTION()
	virtual void NativeInitializeAnimation() override;
	UFUNCTION()
	virtual void NativeBeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void SighUp();

	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void HoldWeapon();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void CleanWeaponData();
	UFUNCTION(BlueprintCallable, Category = "PlayerAnimInstance")
	virtual void UpdateWeaponData(AMasterWeapon* newMasterWeapon); 
};
