// Nublin Studio 2025 All Rights Reserved.

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
