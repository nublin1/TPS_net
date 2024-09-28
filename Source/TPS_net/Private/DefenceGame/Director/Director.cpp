// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/Director/Director.h"

#include "Characters/NPCZombie.h"
#include "Net/UnrealNetwork.h"
#include "Player/Components/HealthComponent.h"

// Sets default values
ADirector::ADirector(): RemainingTimeInSeconds(0)
{
	ZombieWaves = {FZombieWaves(5), FZombieWaves(20), FZombieWaves(30)};
	
	bReplicates = true;
	bAlwaysRelevant = true;
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADirector::BeginPlay()
{
	Super::BeginPlay();
}

void ADirector::StartTimer_Implementation()
{
	RemainingTimeInSeconds = TimerDelay;

	GetWorld()->GetTimerManager().SetTimer(TimerHandleWaves, [this]()
	{
		int32 NewTime = RemainingTimeInSeconds - 1;

		if (NewTime <= 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleWaves);
			NewTime = 0;
			OnTimerExpired.Broadcast();  
		}

		//UE_LOG(LogTemp, Warning, TEXT("Updating RemainingTimeInSeconds: %d"), NewTime);
		ServerUpdateTimer(NewTime);

	}, 1.0f, true);
}

void ADirector::StopTimer_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandleWaves);
}

void ADirector::ServerUpdateTimer_Implementation(const int32 NewRemainingTime)
{
	RemainingTimeInSeconds = NewRemainingTime;
	
	if (OnTimeUpdated.IsBound())
	{
		OnTimeUpdated.Broadcast(RemainingTimeInSeconds);
	}
	
    ClientUpdateTimer(RemainingTimeInSeconds);
}

void ADirector::ClientUpdateTimer_Implementation(int32 NewRemainingTime)
{
	if (OnTimeUpdated.IsBound())
	{
		OnTimeUpdated.Broadcast(NewRemainingTime);
	}
}

void ADirector::HandleZombieDeath(UHealthComponent* HealthComponent)
{
	if (HealthComponent)
	{
		// Bind event to the OnKilled delegate (assuming the OnKilled delegate exists in UHealthComponent)
		HealthComponent->OnKilledDelegate.AddDynamic(this, &ADirector::OnZombieKilledEvent);
	}
}

void ADirector::HandleZombieKilled(AActor* KilledActor)
{
	auto Zombie = Cast<ANPCZombie>(KilledActor);
	
	Zombies.Remove(Zombie);
	if (Zombies.Num() <= 0)
	{
		CurrentNumberOfWave++;
	}
}


// Called every frame
void ADirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADirector::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);

	TArray<FLifetimeProperty> OutLifetimeProps;

	DOREPLIFETIME(ADirector, RemainingTimeInSeconds);
}
