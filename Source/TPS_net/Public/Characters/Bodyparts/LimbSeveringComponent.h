// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LimbSeveringComponent.generated.h"

#pragma region Structs

USTRUCT()
struct FSeveredLimbFrame
{
	GENERATED_BODY()

	FSeveredLimbFrame(){};
	FSeveredLimbFrame(const FName InName, AActor* InActor)
	: BoneName(InName), TargetActor(InActor){}
	
	UPROPERTY()
	FName BoneName = NAME_None;
	UPROPERTY()
	TObjectPtr<AActor> TargetActor = nullptr;
	UPROPERTY()
	FVector Impulse = FVector(0);
	UPROPERTY()
	FTransform Transform;
};

#pragma endregion

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

	// Config
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limb Severing")
	bool bDisableSevering = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limb Severing", meta = (ToolTip = "If true, prevents further severing of already detached limbs (e.g. disallow cutting fingers from a detached arm)."))
	bool bBlockFurtherSevering = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limb Severing")
	bool bSupportAttachedChildMeshes = false;
	UPROPERTY(EditDefaultsOnly, Category = "Limb Severing|Tags")
	FName Tag_KeepAttached = "KeepAttached";
	UPROPERTY(EditDefaultsOnly, Category = "Limb Severing|Tags")
	FName Tag_MoveToSeveredLimb = "MoveToSeveredLimb";
	UPROPERTY(EditDefaultsOnly, Category = "Limb Severing|Tags")
	FName Tag_DetachOnSever = "DetachOnSever"; // "DropOnSever"
	
	
	//Limb Data
	UPROPERTY()
	TMap<FName, TObjectPtr<AActor>> SeveredLimbs;
	TMap<FName, TArray<TObjectPtr<USceneComponent>>> BoneAttachedComponents ;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	ULimbSeveringComponent();

	UFUNCTION(BlueprintCallable, Category="Limb Severing", meta=(ToolTip="Dismembers the specified limb by bone name. Applies an optional impulse to the severed part."))
	virtual void SeverLimbByBone(FName BoneName, FVector Impulse = FVector::ZeroVector);

	//
	UFUNCTION()
	void AddBoneToBlackList(FName BoneName) {BlacklistBones.Add(BoneName);}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Limb Severing")
	TObjectPtr<USkeletalMeshComponent> SeveringMesh;

	//
	UPROPERTY()
	TArray<FSeveredLimbFrame> DelayedSeveredLimbs;
	
	// Defaults
	UPROPERTY(EditAnywhere, Category="Limb Severing", meta = (ToolTip="IMPORTANT: The name of the pelvis bone of the skeleton. This cannot be 'None'."))
	FName PelvisBoneName = FName("Pelvis");
	UPROPERTY(EditAnywhere, Category="Limb Severing")
	TArray<FName> BlacklistBones;
	UPROPERTY(EditAnywhere, Category="Limb Severing")
	TArray<FName> WhitelistBones;
	
	/** Class of the severed limb actor that will be spawned after dismemberment */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Limb Severing", meta = (ToolTip = "Actor class to spawn when a limb is severed."))
	TSubclassOf<AActor> SeveredLimbClass;
	UPROPERTY(EditAnywhere, Category = "Limb Severing", meta = (ToolTip = "Animation Blueprint to use for severed limbs. If null, a default mannequin-based instance will be used."))
	TSubclassOf<USeveredLimbAnimInstance> SeveredLimbAnimClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Limb Severing")
	bool bUseSpecificCollisionObjectType = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Limb Severing", meta = (EditCondition = "bUseSpecificCollisionObjectType", GetOptions = "GetCollisionProfiles"))
	FName CollisionProfileName = TEXT("CharacterMesh");

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
	UFUNCTION()
	bool CheckBoneFilter(const FName BoneName);
	UFUNCTION(Category="Limb Severing")
	static bool IsVirtualBone(FName BoneName);
	UFUNCTION(Category="Limb Severing")
	void FindSkeletalMeshComponent();

	UFUNCTION()
	AActor* CreateSeveredLimb(const FName BoneName, const FTransform& Transform);
	UFUNCTION()
	void FrameDelayedSevering(AActor* Component, const FName BoneName, const FVector& Impulse, const FTransform& Transform);
	UFUNCTION()
	void SeveringLimbFrameDelayed();
	UFUNCTION()
	void CopyLimbProperties(USkeletalMeshComponent* Mesh, USkeletalMeshComponent* Limb);

	UFUNCTION()
	void GetSocketsOnBoneAndChildren(USkeletalMeshComponent* MeshComp,	FName RootBone,	TArray<USkeletalMeshSocket*>& OutSockets);
	UFUNCTION()
	TArray<USceneComponent*> GetAllAttachedMeshes(USkeletalMeshComponent* SkeletalMeshComponent, TSet<FName> UsedSockets);
	UFUNCTION(Category = "Limb Severing")
	void GenerateSeveredLimbPhysicsAsset(FName InLimb);
	UFUNCTION(Category = "Limb Severing", meta = (ToolTip = "Applies a custom AnimInstance to the specified severed limb bone's skeletal mesh component."))
	void ApplyAnimInstanceToSeveredLimb(USkeletalMeshComponent* Component, FName BoneName);
};
