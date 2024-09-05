// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/Director/Director.h"

// Sets default values
ADirector::ADirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADirector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADirector::OnZombieKilled(ANPCCharacter* KilledActor)
{
	Zombies.Remove(KilledActor);
}

// Called every frame
void ADirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

