// Nublin Studio 2025 All Rights Reserved.


#include "Componets/Bullets/CustomBulletProjectile.h"

// Sets default values for this component's properties
UCustomBulletProjectile::UCustomBulletProjectile(): Velocity(), StartPosition()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCustomBulletProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void UCustomBulletProjectile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	HitResultDelegate.Clear();
}


