// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Ladders/MasterLadder.h"


AMasterLadder::AMasterLadder()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bNetLoadOnClient = false;
}

void AMasterLadder::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasterLadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}