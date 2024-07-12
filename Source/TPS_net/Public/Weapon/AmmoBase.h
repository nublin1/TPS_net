#pragma once

#include "CoreMinimal.h"
#include "Data/Weapon/AmmoData.h"
#include "UObject/NoExportTypes.h"
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
	FAmmoCharacteristics GetAmmoCharacteristics() const {return AmmoCharacteristics;}
protected:

	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, Category = "Ammo Characteristics")
	FAmmoCharacteristics AmmoCharacteristics;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
};