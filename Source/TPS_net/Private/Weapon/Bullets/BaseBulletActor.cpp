// Nublin Studio 2025 All Rights Reserved.

#include "Weapon/Bullets/BaseBulletActor.h"


ABaseBulletActor::ABaseBulletActor()
{
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
