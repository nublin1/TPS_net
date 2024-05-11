// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomBulletProjectile.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_NET_API UCustomBulletProjectile : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomBulletProjectile();

protected:
	//Bullet Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Bullet Params", meta=(DisplayName="Velocity"))
	FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Bullet Params", meta=(DisplayName="StartBulletSpeed"))
	float StartBulletSpeed = 75000; // cm/s
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Bullet Params", meta=(DisplayName="BulletLifeTime"))
	float BulletLifeTime = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Bullet Params", meta=(DisplayName="BulletMass"))
	float BulletMass = 0.0116f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Bullet Params", meta=(DisplayName="CrossSection"))
	float CrossSection = 0.49f;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
