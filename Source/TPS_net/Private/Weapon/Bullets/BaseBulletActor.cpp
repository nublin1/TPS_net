// Nublin Studio 2025 All Rights Reserved.

#include "Weapon/Bullets/BaseBulletActor.h"


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

void ABaseBulletActor::SetAutoAim(bool IsAutoAim, FVector NewAimTargetPoint)
{
	bAutoAim = IsAutoAim;
	AimTargetPoint = NewAimTargetPoint;
}

void ABaseBulletActor::InitBullet_Implementation()
{
}
