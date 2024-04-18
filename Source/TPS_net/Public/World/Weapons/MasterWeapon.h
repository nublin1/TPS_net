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
	//====================================================================
	// FUNCTIONS
	//====================================================================	
	AMasterWeapon();

	void UpdateVisual();

	//Getters
	

	//Setters
	void SetWeaponBaseRef(UWeaponBase* _WeaponBase) {WeaponBaseRef = _WeaponBase;}
	void SetSkeletalMeshWeapon(USkeletalMesh* _SkeletalMesh) {SkeletalMeshWeapon = _SkeletalMesh;}
	

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWeaponBase* WeaponBaseRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMesh* SkeletalMeshWeapon;
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
