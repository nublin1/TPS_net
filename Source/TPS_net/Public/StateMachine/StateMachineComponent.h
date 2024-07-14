// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "StateMachineComponent.generated.h"

#pragma region Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChangedSignature, const FGameplayTag&, NewStateTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitStateSignature, const FGameplayTag&, StateTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExitStateSignature, const FGameplayTag&, StateTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTickStateSinganture, float, DeltaTime, const FGameplayTag&, StateTag);
#pragma endregion

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintAssignable)
	FInitStateSignature InitStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FExitStateSignature ExitStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FTickStateSinganture TickStateDelegate;
	UPROPERTY(BlueprintAssignable)
	FStateChangedSignature StateChangedDelegate;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UStateMachineComponent();

	UFUNCTION(BlueprintCallable)
	bool SwitchState(FGameplayTag _StateTag);
	UFUNCTION()
	void OnRep_CurrentStateTag();

	//Getters
	UFUNCTION()
	FGameplayTag GetCurrentStateTag() const { return CurrentStateTag; }
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FString GetCurrentStateTagName() const {return CurrentStateTag.ToString();}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGameplayTag CurrentStateTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InitialStateTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebug = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayTag> StateHistory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StateHistoryLenght = 5;


	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bCanTickState = false;
	void InitState() const;
	void TickState(float DeltaTime) const;
	void ExitState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
