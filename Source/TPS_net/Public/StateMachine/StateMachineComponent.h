// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Interfaces/StateMachineInterface.h"
#include "StateMachineComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UStateMachineComponent : public UActorComponent, public IStateMachineInterface
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
	virtual void SwitchState(FGameplayTag _StateTag) override;
	UFUNCTION()
	virtual void OnRep_CurrentStateTag() override;

	//Getters
	// Implement the delegate accessors
	virtual FInitStateSignature& OnInitState() override { return InitStateDelegate; }
	virtual FExitStateSignature& OnExitState() override { return ExitStateDelegate; }
	virtual FTickStateSinganture& OnTickState() override { return TickStateDelegate; }
	virtual FStateChangedSignature& OnStateChanged() override { return StateChangedDelegate; }
	
	UFUNCTION()
	virtual FGameplayTag GetCurrentStateTag() const override { return CurrentStateTag; }
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	virtual FString GetCurrentStateTagName() const override {return CurrentStateTag.ToString();}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGameplayTag PrevStateTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGameplayTag CurrentStateTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InitialStateTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebug = false;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	virtual void InitState() override;
	virtual void TickState(float DeltaTime) const override;
	virtual void ExitState() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
