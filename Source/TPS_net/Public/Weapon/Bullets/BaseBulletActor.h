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
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Destroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FHitResult Hit;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool SpawnEffectOnGroundAfterHit = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> SpawnOnGroundEffect = nullptr;
	

};
