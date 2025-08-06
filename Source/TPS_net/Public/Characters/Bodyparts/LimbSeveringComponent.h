// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LimbSeveringComponent.generated.h"

/*
 *	LimbSeveringComponent is used for cutting off the
 *	limbs of a Skeletal Mesh. This component uses a control
 *	rig to scale bones based on their bone names.
 */

class USeveredLimbAnimInstance;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPreSevering, FName, BoneName, FVector, Impulse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPostSevering, FName, BoneName, USkeletalMeshComponent*,SeveringMesh);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API ULimbSeveringComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//Delegates
	UPROPERTY(BlueprintAssignable)
	FOnPreSevering OnPreSevering;
	UPROPERTY(BlueprintAssignable)
	FOnPostSevering OnPostSevering;
	
	//Limb Data
	UPROPERTY()
	TMap<FName, TObjectPtr<USkeletalMeshComponent>> SeveredLimbs;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	ULimbSeveringComponent();

	UFUNCTION(BlueprintCallable, Category="Limb Severing", meta=(ToolTip="Dismembers the specified limb by bone name. Applies an optional impulse to the severed part."))
	virtual void SeverLimbByBone(FName BoneName, FVector Impulse = FVector::ZeroVector);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limb Severing")
	TObjectPtr<USkeletalMeshComponent> SeveringMesh;

	// Defaults
	UPROPERTY(EditAnywhere, Category="Limb Severing", meta = (ToolTip="IMPORTANT: The name of the pelvis bone of the skeleton. This cannot be 'None'."))
	FName PelvisBoneName = FName("Pelvis");
	/** Class of the severed limb actor that will be spawned after dismemberment */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Limb Severing", meta = (ToolTip = "Actor class to spawn when a limb is severed."))
	TSubclassOf<AActor> SeveredLimbClass;
	UPROPERTY(EditAnywhere, Category = "Limb Severing", meta = (ToolTip = "Animation Blueprint to use for severed limbs. If null, a default mannequin-based instance will be used."))
	TSubclassOf<USeveredLimbAnimInstance> SeveredLimbAnimClass;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//
	UFUNCTION(Server, Unreliable)
	void LimbSevering_Server(FName BoneName, const FVector& Impulse);
	UFUNCTION(NetMulticast, Unreliable)
	void LimbSevering_Multi(FName BoneName, const FVector& Impulse);
	UFUNCTION()
	void LimbSevering_Internal(FName BoneName, const FVector& Impulse);

	virtual void PreSevering(const FName BoneName, FVector Impulse);
	virtual void PostSevering(const FName BoneName, USkeletalMeshComponent* DismemberMesh);

private:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(Category="Limb Severing")
	static bool IsVirtualBone(FName BoneName);
	UFUNCTION(Category="Limb Severing")
	void FindSkeletalMeshComponent();

	UFUNCTION()
	void CopyLimbProperties(USkeletalMeshComponent* Mesh, USkeletalMeshComponent* Limb);
	
	UFUNCTION(Category = "Limb Severing")
	void GenerateSeveredLimbPhysicsAsset(FName InLimb);
	UFUNCTION(Category = "Limb Severing", meta = (ToolTip = "Applies a custom AnimInstance to the specified severed limb bone's skeletal mesh component."))
	void ApplyAnimInstanceToSeveredLimb(USkeletalMeshComponent* Component, FName BoneName);
};
