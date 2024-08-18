// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/WeaponBase.h"
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

	void UpdateVisual() const;

	UFUNCTION()
	void DecreaseRoundsInMagazine() {RoundsInMagazine--;}
	UFUNCTION(BlueprintCallable)
	void Reload();

	//Getters
	UWeaponBase* GetWeaponBaseRef() const { return WeaponBaseRef; }
	USkeletalMeshComponent* GetSkeletalMeshWeapon() const { return SkeletalMeshWeapon; }
	UStaticMeshComponent* GetTargetPoint() { return TargetPoint; }

	uint16 GetRoundsInMagazine() const {return RoundsInMagazine;}
	uint16 GetMagazineSize() const {return WeaponBaseRef->GetCharacteristicsOfTheWeapon().MagazineSize;}

	//Setters
	void SetWeaponBaseRef(UWeaponBase* _WeaponBase) { WeaponBaseRef = _WeaponBase; }

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UWeaponBase* WeaponBaseRef;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* SkeletalMeshWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* TargetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StartingWeapon;

	//
	uint16 RoundsInMagazine = 10;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
