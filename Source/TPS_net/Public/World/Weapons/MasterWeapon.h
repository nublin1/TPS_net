// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/WeaponBase.h"
#include "MasterWeapon.generated.h"

class UWeaponBase;

#pragma region Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteReloadSignature, int, RoundsInMagazine);
#pragma endregion

UCLASS()
class TPS_NET_API AMasterWeapon : public AActor
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Delegates
	FOnCompleteReloadSignature OnCompleteReloadDelegate;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================	
	AMasterWeapon();

	UFUNCTION()
	void InitWeaponBaseData();
	UFUNCTION()
	void UpdateVisual();
	UFUNCTION(BlueprintCallable)
	void ToggleBoneVisibility(FName BoneName);
	

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartFire();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();
	UFUNCTION(BlueprintImplementableEvent)
	void OnStopFire();

	UFUNCTION(BlueprintCallable)
	void PlayShootEffect(UParticleSystem* ParticleSystem, FName SocketName);
	UFUNCTION(Server, Unreliable)
	void PlayShootEffect_Server(UParticleSystem* ParticleSystem, FName SocketName);
	UFUNCTION(NetMulticast, Unreliable)
	void PlayShootEffect_Multicast(UParticleSystem* ParticleSystem, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void DecreaseRoundsInMagazine();
	UFUNCTION(Server, Unreliable)
	void ServerDecreaseRoundsInMagazine();
	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(Server, Unreliable)
	void ServerReload();
	UFUNCTION(BlueprintCallable)
	virtual void SwitchFireMode();

	//Getters
	UWeaponBase* GetWeaponBaseRef() const { return WeaponBaseRef; }
	USkeletalMeshComponent* GetSkeletalMeshWeapon() const { return SkeletalMeshWeapon; }
	//UStaticMeshComponent* GetTargetPoint() { return TargetPoint; }

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
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> TargetPointPtr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ClipBoneName;

	//
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_RoundsInMagazine)
	uint16 RoundsInMagazine = 10;
	UPROPERTY(Replicated, BlueprintReadOnly)
	EFireMode SelectedFireMode = EFireMode::None;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StartingWeapon;

	// Recoil
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRecoiling = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentRecoilTime;
	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnRep_WeaponBaseRef();
	UFUNCTION()
	void OnRep_RoundsInMagazine() const;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
};
