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
	virtual ~UAmmoBase() override;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FAmmoCharacteristics AmmoCharacteristics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Characteristics")
	FBulletBehaviour AmmoBehaviour;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
};