// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileFactory.h"
#include "UObject/NoExportTypes.h"
#include "BulletProjectileFactory.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UBulletProjectileFactory : public UObject, public IProjectileFactory
{
	GENERATED_BODY()

public:
	virtual AActor* CreateProjectile(
		UWorld* World,
		UBlueprint* BulletBlueprint,
		const FVector& SpawnLocation,
		const FRotator& SpawnRotation,
		const FActorSpawnParameters& SpawnParameters) override
	{
		return World->SpawnActor<AActor>(BulletBlueprint->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParameters);
	}
};
