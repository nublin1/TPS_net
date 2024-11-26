// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBulletActor.generated.h"

class UAmmoBase;

UCLASS()
class TPS_NET_API ABaseBulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseBulletActor();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Destroy();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
