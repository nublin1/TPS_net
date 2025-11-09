#include "Weapon/AmmoBase.h"

#include "Net/UnrealNetwork.h"

UAmmoBase::UAmmoBase()
{
}

void UAmmoBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAmmoBase, AmmoCharacteristics);
	DOREPLIFETIME(UAmmoBase, AmmoBehaviour);
	DOREPLIFETIME(UAmmoBase, AmmoAssets);
}

void UAmmoBase::SetAmmoData(const FAmmoCharacteristics& NewAmmoCharacteristics, const FBulletBehaviour& NewAmmoBehaviour,
	const FAmmoAssets& NewAmmoAssets)
{
	AmmoCharacteristics = NewAmmoCharacteristics;
	AmmoBehaviour = NewAmmoBehaviour;
	AmmoAssets = NewAmmoAssets;
}
