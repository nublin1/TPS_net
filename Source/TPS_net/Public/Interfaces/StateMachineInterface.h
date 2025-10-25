// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "StateMachineInterface.generated.h"

// Delegate declarations
#pragma region Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateChangedSignature, AActor*, Actor, const FGameplayTag&, NewStateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitStateSignature, const FGameplayTag&, StateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExitStateSignature, const FGameplayTag&, ExitStateTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickStateSinganture, float, DeltaTime, const FGameplayTag&, StateTag);
#pragma endregion

struct FGameplayTag;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStateMachineInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPS_NET_API IStateMachineInterface
{
	GENERATED_BODY()

public:
	// Delegate properties
	virtual FInitStateSignature& OnInitState() = 0;
	virtual FExitStateSignature& OnExitState() = 0;
	virtual FTickStateSinganture& OnTickState() = 0;
	virtual FStateChangedSignature& OnStateChanged() = 0;

	// Functions that need to be implemented
	virtual void SwitchState(FGameplayTag _StateTag) = 0;
	virtual void OnRep_CurrentStateTag() = 0;
	virtual FGameplayTag GetCurrentStateTag() const = 0;
	virtual FString GetCurrentStateTagName() const = 0;

protected:
	bool bCanTickState = false;
	
	//
	virtual void InitState() = 0;
	virtual void TickState(float DeltaTime) const= 0;
	virtual void ExitState()= 0;
};
