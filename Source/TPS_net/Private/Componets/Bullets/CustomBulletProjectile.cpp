// Fill out your copyright notice in the Description page of Project Settings.


#include "Componets/Bullets/CustomBulletProjectile.h"

// Sets default values for this component's properties
UCustomBulletProjectile::UCustomBulletProjectile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCustomBulletProjectile::Init()
{
	if (!BulletAmmoData)
		return;
	
	Velocity =  GetOwner()->GetActorForwardVector() * BulletAmmoData->GetAmmoCharacteristics().StartBulletSpeed;
	StartPosition = GetOwner()->GetActorLocation();
	IsInitialized = true;
	
	if(GetOwner()){
		GetOwner()->GetWorldTimerManager().SetTimer(DestroyHandle, this, &UCustomBulletProjectile::DestroyReq, BulletAmmoData->GetAmmoCharacteristics().BulletLifeTime, false);
	    
	}
}

void UCustomBulletProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void UCustomBulletProjectile::HitDetected()
{
	if(HitResultDelegate.IsBound())
	{
		HitResultDelegate.Broadcast(OutHit);
	}
}

void UCustomBulletProjectile::DestroyReq()
{
	if (GetOwner()->GetWorldTimerManager().IsTimerActive(DestroyHandle))
		GetOwner()->GetWorldTimerManager().ClearTimer(DestroyHandle);

	IsNeedToDestroy = true;
}


// Called every frame
void UCustomBulletProjectile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

