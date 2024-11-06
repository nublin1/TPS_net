#pragma once

#include "CoreMinimal.h"
#include "Data/Weapon/AmmoData.h"

#include "AmmoBase.generated.h"



UCLASS(Blueprintable)
class TPS_NET_API UAmmoBase : public UObject
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	UAmmoBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }

	// getters
	UFUNCTION(BlueprintCallable)
	FAmmoCharacteristics GetAmmoCharacteristics()  {return AmmoCharacteristics;}
	FBulletBehaviour GetAmmoBehaviour() const {return AmmoBehaviour;}

	// Setters
	void SetAmmoCharacteristics(const FAmmoCharacteristics& NewAmmoCharacteristics) {AmmoCharacteristics = NewAmmoCharacteristics;}
	void SetAmmoBehaviour(const FBulletBehaviour& NewAmmoBehaviour) {AmmoBehaviour = NewAmmoBehaviour;}
	
protected:

	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FAmmoCharacteristics AmmoCharacteristics;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FBulletBehaviour AmmoBehaviour;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
};