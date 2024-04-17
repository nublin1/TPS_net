// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Weapons/MasterWeapon.h"


AMasterWeapon::AMasterWeapon(): WeaponBaseRef(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();	
}


void AMasterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

