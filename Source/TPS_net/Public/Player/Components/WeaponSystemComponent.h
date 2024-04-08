// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystemComponent.generated.h"


class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponSystemComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeapon* CurrentWeaponInHands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeapon* WeaponPistolHolster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeapon* WeaponPrimaryHolster;
	
	virtual void BeginPlay() override;

public:		
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
