// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Ladders/ProceduralLadder.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AProceduralLadder::AProceduralLadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bNetLoadOnClient = false;
}

// Called when the game starts or when spawned
void AProceduralLadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProceduralLadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}