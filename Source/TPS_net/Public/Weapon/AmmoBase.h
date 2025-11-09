#pragma once

#include "CoreMinimal.h"
#include "Data/Weapon/AmmoData.h"

#include "AmmoBase.generated.h"



UCLASS(Blueprintable)
class TPS_NET_API UAmmoBase : public UObject
{
	GENERATED_BODY()

public:
	UAmmoBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	// getters
	UFUNCTION(BlueprintCallable)
	FAmmoCharacteristics GetAmmoCharacteristics()  {return AmmoCharacteristics;}
	FBulletBehaviour GetAmmoBehaviour() const {return AmmoBehaviour;}

	// Setters
	void SetAmmoData (const FAmmoCharacteristics& NewAmmoCharacteristics, const FBulletBehaviour& NewAmmoBehaviour, const FAmmoAssets& NewAmmoAssets);
	
protected:

	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FAmmoCharacteristics AmmoCharacteristics;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FBulletBehaviour AmmoBehaviour;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FAmmoAssets AmmoAssets;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
};