// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/Fort/DefenseFort.h"

#include "Components/BoxComponent.h"

class UBoxComponent;
// Sets default values
ADefenseFort::ADefenseFort()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

void ADefenseFort::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

// Called when the game starts or when spawned
void ADefenseFort::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ADefenseFort::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

