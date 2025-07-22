
#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimSequenceBase.h"

#include "AnimationStructLibrary.generated.h"


USTRUCT(BlueprintType)
struct FAnimGraphInAir
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - In Air")
	bool bJumped = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - In Air")
	float JumpPlayRate = 1.2f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - In Air")
	float FallSpeed = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - In Air")
	float LandPrediction = 1.0f;
};

USTRUCT(BlueprintType)
struct FAnimCharacterInformation
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character Information")
	FVector2D MovementVector;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character Information")
	bool bShouldMove;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character Information")
	float Speed = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character Information")
	FRotator AimingRotation = FRotator();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character Information")
	FRotator CharacterActorRotation = FRotator();
	
};

USTRUCT(BlueprintType)
struct FAnimGraphAimingValues
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Aiming Values")
	FRotator SmoothedAimingRotation;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Aiming Values")
	FVector2D AimingAngle;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Aiming Values")
	FVector2D SmoothedAimingAngle;
};

USTRUCT(BlueprintType)
struct FAnimGraphLayerBlending
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float BasePose_N = 1.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Legs = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Pelvis = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Pelvis_Add = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Spine = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Spine_Add = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Head = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Head_Add = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Arm_L = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Arm_L_Add = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Arm_R = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Anim Graph - Layer Blending")
	float Arm_R_Add = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Anim Graph - Layer Blending")
	bool EnableHandIK_L = 0.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Anim Graph - Layer Blending")
	bool EnableHandIK_R = 1.0f;
};

USTRUCT(BlueprintType)
struct FAnimConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Configuration")
	float SmoothedAimingRotationInterpSpeed = 10.0f;
};