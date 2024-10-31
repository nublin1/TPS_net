// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHealthInterface.h"
#include "Barricade.generated.h"

class UAIPointGeneratorComponent;

UCLASS()
class TPS_NET_API ABarricade : public AActor, public IIHealthInterface
{
	GENERATED_BODY()
	
public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	ABarricade();

	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const override;

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAIPointGeneratorComponent> PointGeneratorComponent;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void BeginPlay() override;

	UFUNCTION()
	void ActorDestroyed (AActor* DestroyedActor, AController* EventInstigator);
	UFUNCTION(Server, Unreliable)
	void Server_ActorDestroyed(AActor* DestroyedActor);
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_ActorDestroyed(AActor* DestroyedActor);

public:	
	virtual void Tick(float DeltaTime) override;

};
