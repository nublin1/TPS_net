// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Weapons/MasterWeapon.h"

// Sets default values
AMasterWeapon::AMasterWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

