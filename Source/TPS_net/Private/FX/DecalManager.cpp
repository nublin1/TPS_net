// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/DecalManager.h"

#include "Kismet/GameplayStatics.h"

UDecalComponent* UDecalManager::SpawnDecalComponent(UMaterialInstance* MaterialInstance,
                                                    USceneComponent* AttachComponent, FName AttachPointName, FVector Location, FRotator Rotation, FVector Scale,
                                                    EAttachLocation::Type LocationType, float LifeSpan, UObject* WorldContextObject)
{
	if (!MaterialInstance) return nullptr;
	
	UDecalComponent* Decal = nullptr;

	if (AttachComponent)
	{
		Decal = UGameplayStatics::SpawnDecalAttached (MaterialInstance, Scale, AttachComponent, AttachPointName, Location, Rotation, LocationType, LifeSpan);
		return Decal;
	}
	else
	{
		if (!WorldContextObject) return nullptr;
		
		Decal = UGameplayStatics::SpawnDecalAtLocation(WorldContextObject, MaterialInstance, Scale, Location, Rotation, LifeSpan);
		return Decal;
	}
}
