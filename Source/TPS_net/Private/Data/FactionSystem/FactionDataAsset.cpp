// Nublin Studio 2025 All Rights Reserved.


#include "Data/FactionSystem/FactionDataAsset.h"

#include "Data/FactionSystem/FactionAttitude.h"

UFactionDataAsset::UFactionDataAsset()
{
}

EFactionAttitude UFactionDataAsset::GetAttitudeTo(const UFactionDataAsset* Other) const
{
	if (!Other)
		return EFactionAttitude::Neutral;

	for (const FFactionRelation& Relation : Relations)
	{
		if (Relation.OtherFaction == Other->FactionName)
			return Relation.Attitude;
	}

	// Не задано - проверяем родителя
	if (ParentFaction)
		return ParentFaction->GetAttitudeTo(Other);

	return EFactionAttitude::Neutral;
}
