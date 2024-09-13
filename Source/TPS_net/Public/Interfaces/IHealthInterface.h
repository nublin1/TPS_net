// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHealthInterface.generated.h"


class UHealthComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UIHealthInterface : public UInterface
{
	GENERATED_BODY()
};


class TPS_NET_API IIHealthInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const = 0;
};