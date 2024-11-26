// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bullets/BaseBulletActor.h"

#include "Componets/Bullets/CustomBulletProjectile.h"

// Sets default values
ABaseBulletActor::ABaseBulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseBulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseBulletActor::Destroy()
{
	K2_DestroyActor();
}

void ABaseBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
