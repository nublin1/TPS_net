// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/StateMachineComponent.h"

#include "Net/UnrealNetwork.h"


UStateMachineComponent::UStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//InitialStateTag = FGameplayTag::RequestGameplayTag(TEXT("Idle"));
	SetIsReplicatedByDefault(true);
	SetIsReplicated(true);
}

void UStateMachineComponent::SwitchState(FGameplayTag _StateTag)
{
	if (!_StateTag.MatchesTagExact(CurrentStateTag))
	{
		bCanTickState = false;
		
		ExitState();
		CurrentStateTag = _StateTag;
		InitState();

		bCanTickState= true;
		OnRep_CurrentStateTag();
		if(StateChangedDelegate.IsBound())
		{
			
			StateChangedDelegate.Broadcast(GetOwner(),CurrentStateTag);
		}
	}
	else
	{
		if (bDebug)
		{
			
		}
	}
}

void UStateMachineComponent::InitState()
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

void UStateMachineComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
	DOREPLIFETIME(UStateMachineComponent, CurrentStateTag);
}

void UStateMachineComponent::OnRep_CurrentStateTag()
{
	// if (GEngine)
	// {
	// 	FString Role = GetOwnerRole() == ROLE_Authority ? "Server" : "Client";
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OnRep_CurrentStateTag for %s: %s, Role: %s"), *GetOwner()->GetName(), *CurrentStateTag.ToString(), *Role));
	// }
	
	InitState();
	if (StateChangedDelegate.IsBound())
	{
		StateChangedDelegate.Broadcast(GetOwner(), CurrentStateTag);
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
		if (GPlayInEditorID == 0)
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("CurrentState for %s: %s"), *GetOwner()->GetName(), *CurrentStateTag.ToString()));
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString::Printf(TEXT("CurrentState for %s: %s"), *GetOwner()->GetName(), *CurrentStateTag.ToString()));
		}

		if (StateHistory.Num() > 0)
		{
			for (int i=0; i<StateHistory.Num(); i++)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString::Printf(TEXT("%s"), *StateHistory[i].ToString()));
			}
		}
	}
}

