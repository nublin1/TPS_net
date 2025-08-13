// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DecalManager.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UDecalManager : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UDecalComponent* SpawnDecalComponent(UMaterialInstance* MaterialInstance = nullptr,
		USceneComponent* AttachComponent = nullptr,
		FName AttachPointName = NAME_None,
		FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1),
		EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset,
		float LifeSpan = 0, UObject* WorldContextObject = nullptr);
};
