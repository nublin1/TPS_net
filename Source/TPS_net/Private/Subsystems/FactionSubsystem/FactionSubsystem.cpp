// Nublin Studio 2025 All Rights Reserved.


#include "Subsystems/FactionSubsystem/FactionSubsystem.h"

#include "Data/FactionSystem/FactionDataAsset.h"

UFactionSubsystem::UFactionSubsystem()
{
}

UFactionDataAsset* UFactionSubsystem::GetFactionByName(FName Name) const
{
	for (UFactionDataAsset* Faction : AllFactions)
	{
		if (Faction && Faction->FactionName == Name)
			return Faction;
	}
	return nullptr;
}

EFactionAttitude UFactionSubsystem::GetAttitudeBetween(FName FactionA, FName FactionB) const
{
	UFactionDataAsset* FA = GetFactionByName(FactionA);
	UFactionDataAsset* FB = GetFactionByName(FactionB);

	if (!FA || !FB)
		return EFactionAttitude::Neutral;

	return FA->GetAttitudeTo(FB);
}

void UFactionSubsystem::RegisterFaction(UFactionDataAsset* Faction)
{
	if (Faction && !AllFactions.Contains(Faction))
	{
		AllFactions.Add(Faction);
	}
}
