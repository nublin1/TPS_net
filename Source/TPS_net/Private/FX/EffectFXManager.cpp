// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/EffectFXManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UNiagaraComponent* UEffectFXManager::SpawnFXEffect( UNiagaraSystem* Effect, 
	USceneComponent* AttachTo,
	FName SocketName,
	FVector Location,
	FRotator Rotation,
	FVector Scale,
	bool bAutoDestroy)
{
	if (!Effect)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnNiagaraEffect: Effect is null"));
		return nullptr;
	}

	UNiagaraComponent* NiagaraComp = nullptr;

	if (AttachTo)
	{
		NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			Effect,
			AttachTo,
			SocketName,
			Location,
			Rotation,
			EAttachLocation::KeepRelativeOffset,
			true, // AutoDestroy
			true  // AutoActivate
		);
	}
	else
	{
		NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			AttachTo ? AttachTo->GetWorld() : GWorld,
			Effect,
			Location,
			Rotation,
			Scale,
			true,  // AutoDestroy
			true,  // AutoActivate
			ENCPoolMethod::None
		);
	}

	if (NiagaraComp && !Scale.Equals(FVector(1.f)))
	{
		NiagaraComp->SetWorldScale3D(Scale);
	}

	return NiagaraComp;
}

UNiagaraSystem* UEffectFXManager::LoadFX(const FString& Path)
{
	if (Path.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadFX: Path is empty"));
		return nullptr;
	}

	FSoftObjectPath AssetPath(Path);
	UObject* LoadedObj = AssetPath.TryLoad();
	if (!LoadedObj)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadFX: Failed to load NiagaraSystem at path: %s"), *Path);
		return nullptr;
	}

	UNiagaraSystem* NiagaraSystem = Cast<UNiagaraSystem>(LoadedObj);
	if (!NiagaraSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadFX: Loaded asset is not a NiagaraSystem: %s"), *Path);
		return nullptr;
	}

	return NiagaraSystem;
}
