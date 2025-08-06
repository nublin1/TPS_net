// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SeveredLimbAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API USeveredLimbAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "SeveredLimbAnimInstance")
	FName PelvisBoneName = "Pelvis";

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "SeveredLimbAnimInstance")
	FName LimbBoneName = "upperarm_l";
};
