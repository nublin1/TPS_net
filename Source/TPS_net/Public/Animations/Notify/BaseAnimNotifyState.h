// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BaseAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UBaseAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NotifyState")
	FName NotifyStateID;

	//
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UFUNCTION(Category = "NotifyState")
	void OnNotifyStateInterrupted();

	UFUNCTION(Category = "NotifyState")
	void OnNotifyStateFinishedNormally();


protected:
	// Вспомогательный метод для получения AnimInstance как UMyAnimInstance
	UAnimInstance* GetAnimInstance(USkeletalMeshComponent* MeshComp) const;
};
