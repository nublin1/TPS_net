// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Weapon/AmmoData.h"
#include "Weapon/AmmoBase.h"
#include "CustomBulletProjectile.generated.h"

#pragma region Delegates
class UAmmoBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitSignature, const FHitResult&, HitResult);

#pragma endregion


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

	UFUNCTION()
	void Init();

	//Getters
	UAmmoBase* GetAmmoData() {return BulletAmmoData;}
	
	float GetStartBulletSpeed() const { return BulletAmmoData->GetAmmoCharacteristics().StartBulletSpeed; }	
	float GetBulletLifeTime() const { return BulletAmmoData->GetAmmoCharacteristics().BulletLifeTime; }	
	float GetBulletMass() const { return BulletAmmoData->GetAmmoCharacteristics().BulletMass; }
	float GetCrossSection() const { return BulletAmmoData->GetAmmoCharacteristics().CrossSection; }

	// Setters
	void SetAmmoData( TObjectPtr<UAmmoBase> NewAmmoData ) {BulletAmmoData = NewAmmoData;}

protected:
	UPROPERTY(BlueprintAssignable)
	FHitSignature HitResultDelegate;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TObjectPtr<UAmmoBase> BulletAmmoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInitialized = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition;

	//HitResult
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult OutHit;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void HitDetected();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
