// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterWeapon.generated.h"

class UWeaponBase;

UCLASS()
class TPS_NET_API AMasterWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterWeapon();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWeaponBase* WeaponBaseRef;
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
