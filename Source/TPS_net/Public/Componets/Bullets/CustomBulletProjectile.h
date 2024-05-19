// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomBulletProjectile.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UCustomBulletProjectile : public UActorComponent
{
	GENERATED_BODY()

public:
	//====================================================================
	// FUNCTIONS
	//====================================================================
	// Sets default values for this component's properties
	UCustomBulletProjectile();

	//Getters
	float GetStartBulletSpeed() const { return StartBulletSpeed; }	
	float GetBulletLifeTime() const { return BulletLifeTime; }	
	float GetBulletMass() const { return BulletMass; }
	float GetCrossSection() const { return CrossSection; }

	//Setters
	void SetStartBulletSpeed(const float _StartBulletSpeed) { this->StartBulletSpeed = _StartBulletSpeed; }
	void SetBulletMass(const float _BulletMass) { this->BulletMass = _BulletMass; }
	void SetBulletLifeTime(const float _BulletLifeTime) { this->BulletLifeTime = _BulletLifeTime; }
	void SetCrossSection(const float _CrossSection) { this->CrossSection = _CrossSection; }

protected:
	//Bullet Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Params", meta=(DisplayName="Velocity"))
	FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Params", meta=(DisplayName="StartBulletSpeed"))
	float StartBulletSpeed = 75000; // cm/s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Params", meta=(DisplayName="BulletLifeTime"))
	float BulletLifeTime = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Params", meta=(DisplayName="BulletMass"))
	float BulletMass = 0.116f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Params", meta=(DisplayName="CrossSection"))
	float CrossSection = 0.49f;

	// Behaviour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta=(DisplayName="IsCanRicochet"))
	bool IsCanRicochet = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta=(DisplayName="IsEffectOfGravity"))
	bool IsEffectOfGravity = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour", meta=(DisplayName="IsEffectOfDragForce"))
	bool IsEffectOfDragForce = true;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
