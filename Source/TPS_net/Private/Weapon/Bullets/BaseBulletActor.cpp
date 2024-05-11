// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bullets/BaseBulletActor.h"

// Sets default values
ABaseBulletActor::ABaseBulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

