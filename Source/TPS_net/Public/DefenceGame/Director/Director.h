// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Director.generated.h"

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerBeetweenWavesStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerBeetweenWavesExpired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeUpdated, int, RemainingTime);

#pragma endregion

class UHealthComponent;
class ANPCZombie;

USTRUCT(Blueprintable)
struct FZombieWaves
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ZombieCount;
	
	FZombieWaves() : ZombieCount(10) {}
	explicit FZombieWaves(const int InZombieCount) : ZombieCount(InZombieCount) {}
};

UCLASS()
class TPS_NET_API ADirector : public AActor
{
	GENERATED_BODY()
	
public:	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintAssignable)
	FOnTimerBeetweenWavesStarted OnTimerBeetweenWavesStarted;
	UPROPERTY(BlueprintAssignable)
	FOnTimerBeetweenWavesExpired OnTimerBeetweenWavesExpired;
	UPROPERTY(BlueprintAssignable)
	FOnTimeUpdated OnTimeUpdated; 
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	ADirector();
	
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void StartTimer();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void StopTimer();

	UFUNCTION(BlueprintCallable)
	bool CheckPathIseRachable(FVector StartLocation, FVector EndLocation);

	// Setters
	UFUNCTION(BlueprintCallable)
	void SetTimerDelay(int NewTime) {TimerDelay = NewTime;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadOnly)
	int CurrentNumberOfWave = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FZombieWaves> ZombieWaves;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ANPCZombie*> Zombies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int FirstWaveDelay = 2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int DelayBetweenWaves = 60;

	UPROPERTY(Replicated)
	int32 RemainingTimeInSeconds;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;
	
	UFUNCTION(Server, Reliable)
	void ServerUpdateTimer(int32 NewRemainingTime);
	UFUNCTION(NetMulticast, Reliable)
	void ClientUpdateTimer(int32 NewRemainingTime);

	UFUNCTION(BlueprintCallable)
	virtual void HandleZombieDeath(UHealthComponent* HealthComponent);
	UFUNCTION(BlueprintImplementableEvent)
	void OnZombieKilledEvent(AActor* KilledActor, AController* EventInstigator);
	UFUNCTION(BlueprintCallable)
	void HandleZombieKilled(AActor* KilledActor);

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const override;

private:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	FTimerHandle TimerHandleWaves;
	UPROPERTY()
	int TimerDelay = 60;
	
};
