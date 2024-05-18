// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/StateMachineComponent.h"


UStateMachineComponent::UStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//InitialStateTag = FGameplayTag::RequestGameplayTag(TEXT("Idle"));
}

bool UStateMachineComponent::SwitchState(FGameplayTag _StateTag)
{
	if (!_StateTag.MatchesTagExact(CurrentStateTag))
	{
		bCanTickState = false;
		
		ExitState();
		CurrentStateTag = _StateTag;
		InitState();

		bCanTickState= true;
		if(StateChangedDelegate.IsBound())
		{
			StateChangedDelegate.Broadcast(CurrentStateTag);
		}
		return true;
	}
	else
	{
		if (bDebug)
		{
			
		}
	}

	return false;
	
}

void UStateMachineComponent::InitState() const
{
	if (InitStateDelegate.IsBound())
	{
		InitStateDelegate.Broadcast(CurrentStateTag);
	}
}

void UStateMachineComponent::TickState(float DeltaTime) const
{
	if (TickStateDelegate.IsBound())
	{
		TickStateDelegate.Broadcast(DeltaTime, CurrentStateTag);
	}
}

void UStateMachineComponent::ExitState()
{
	if (StateHistory.Num()>= StateHistoryLenght)
	{
		StateHistory.RemoveAt(0);
	}
	StateHistory.Push(CurrentStateTag);
	
	if (ExitStateDelegate.IsBound())
	{
		ExitStateDelegate.Broadcast(CurrentStateTag);
	}
}

void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	SwitchState(InitialStateTag);	
}

void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanTickState)
	{
		TickState(DeltaTime);
	}

	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("CurrentState for %s: %s"), *GetOwner()->GetName(), *CurrentStateTag.ToString()));

		if (StateHistory.Num() > 0)
		{
			for (int i=0; i<StateHistory.Num(); i++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString::Printf(TEXT("%s"), *StateHistory[i].ToString()));
			}
		}
	}
}

