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

	UFUNCTION()
	void InitWeaponBaseData();
	UFUNCTION()
	void UpdateVisual();

	UFUNCTION()
	void DecreaseRoundsInMagazine() {RoundsInMagazine--;}
	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintCallable)
	virtual void SwitchFireMode();

	//Getters
	UWeaponBase* GetWeaponBaseRef() const { return WeaponBaseRef; }
	USkeletalMeshComponent* GetSkeletalMeshWeapon() const { return SkeletalMeshWeapon; }
	UStaticMeshComponent* GetTargetPoint() { return TargetPoint; }

	UFUNCTION(BlueprintCallable)
	EFireMode GetSelectedFireMode() {return SelectedFireMode;}
	UFUNCTION()
	uint16 GetRoundsInMagazine() const {return RoundsInMagazine;}
	UFUNCTION()
	uint16 GetMagazineSize() const {return WeaponBaseRef->GetCharacteristicsOfTheWeapon().MagazineSize;}

	//Setters
	void SetWeaponBaseRef(UWeaponBase* _WeaponBase);
	void SetWeaponTableAndName(UDataTable* Table, FName Name);

protected:
	UPROPERTY(Replicated,ReplicatedUsing = OnRep_WeaponBaseRef, BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UWeaponBase> WeaponBaseRef;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* SkeletalMeshWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* TargetPoint;

	//
	UPROPERTY()
	uint16 RoundsInMagazine = 10;
	UPROPERTY()
	EFireMode SelectedFireMode = EFireMode::None;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StartingWeapon;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnRep_WeaponBaseRef();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
};
