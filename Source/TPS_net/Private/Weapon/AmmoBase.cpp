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
}
