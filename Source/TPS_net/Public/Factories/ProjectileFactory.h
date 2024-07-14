// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectileFactory.generated.h"


UINTERFACE(MinimalAPI)
class UProjectileFactory : public UInterface
{
	GENERATED_BODY()
};

class TPS_NET_API IProjectileFactory 
{
	GENERATED_BODY()
	
public:
	virtual AActor* CreateProjectile(
		UWorld* World,
		UBlueprint* BulletBlueprint,
		const FVector& SpawnLocation,
		const FRotator& SpawnRotation,
		const FActorSpawnParameters& SpawnParameters) = 0;

};
