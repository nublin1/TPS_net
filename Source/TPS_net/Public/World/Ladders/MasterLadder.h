// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterLadder.generated.h"

UCLASS()
class TPS_NET_API AMasterLadder : public AActor
{
	GENERATED_BODY()
	
public:	
	AMasterLadder();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
};
