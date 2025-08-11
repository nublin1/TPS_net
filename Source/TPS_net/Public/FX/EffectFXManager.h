// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectFXManager.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class TPS_NET_API UEffectFXManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UNiagaraComponent* SpawnFXEffect(
		UNiagaraSystem* Effect,
		USceneComponent* AttachTo = nullptr,
		FName SocketName = NAME_None,
		FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator,
		FVector Scale = FVector(1.f),
		bool bAutoDestroy = true
	);

	/** FX */
	UFUNCTION(BlueprintCallable)
	static UNiagaraSystem* LoadFX(const FString& Path);
};
