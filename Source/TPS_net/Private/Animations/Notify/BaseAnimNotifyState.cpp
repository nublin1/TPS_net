// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notify/BaseAnimNotifyState.h"

void UBaseAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UAnimInstance* AnimInstance = GetAnimInstance(MeshComp);
	if (AnimInstance)
	{
		UE_LOG(LogTemp, Log, TEXT("NotifyBegin: %s on %s. Notifying AnimInstance."), *NotifyStateID.ToString(), *Animation->GetName());
		// Сообщаем AnimInstance, что этот NotifyState начался
		//AnimInstance->NotifyStateBegan(this, Animation); 
	}
}

void UBaseAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	UAnimInstance* AnimInstance = GetAnimInstance(MeshComp);
	if (AnimInstance)
	{
		UE_LOG(LogTemp, Log, TEXT("NotifyEnd: %s on %s. Notifying AnimInstance."), *NotifyStateID.ToString(), *Animation->GetName());
		// Сообщаем AnimInstance, что этот NotifyState завершился (неважно, как)
		//AnimInstance->NotifyStateEnded(this, Animation);
	}
}

void UBaseAnimNotifyState::OnNotifyStateInterrupted()
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyState %s was interrupted!"), *NotifyStateID.ToString());
	// Здесь логика, когда NotifyState был прерван
}

void UBaseAnimNotifyState::OnNotifyStateFinishedNormally()
{
	UE_LOG(LogTemp, Display, TEXT("NotifyState %s finished normally."), *NotifyStateID.ToString());
	// Здесь логика, когда NotifyState завершился без прерывания
}

UAnimInstance* UBaseAnimNotifyState::GetAnimInstance(USkeletalMeshComponent* MeshComp) const
{
	if (MeshComp)
	{
		return Cast<UAnimInstance>(MeshComp->GetAnimInstance());
	}
	return nullptr;
}
