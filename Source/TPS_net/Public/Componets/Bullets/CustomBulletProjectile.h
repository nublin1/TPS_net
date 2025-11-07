// Nublin Studio 2025 All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Weapon/AmmoData.h"
#include "Weapon/AmmoBase.h"
#include "CustomBulletProjectile.generated.h"

class UAmmoBase;


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_NET_API UCustomBulletProjectile : public UActorComponent
{
	GENERATED_BODY()

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitSignature, const FHitResult&, HitResult);
#pragma endregion

public:
	// Sets default values for this component's properties
	UCustomBulletProjectile();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FHitSignature HitResultDelegate;	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
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
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TObjectPtr<UAmmoBase> BulletAmmoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInitialized = false;
	UPROPERTY(BlueprintReadWrite)
	bool IsNeedToDestroy = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition;
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> ActorsToIgnore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETraceTypeQuery> CollisionChannel = ETraceTypeQuery::TraceTypeQuery1;

	//HitResult
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult OutHit;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	virtual void HitDetected();

	UFUNCTION(BlueprintCallable)
	virtual void DestroyReq();

private:
	FTimerHandle DestroyHandle;
};
