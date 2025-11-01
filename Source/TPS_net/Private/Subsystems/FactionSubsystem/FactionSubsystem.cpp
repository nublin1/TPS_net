// Nublin Studio 2025 All Rights Reserved.


#include "Subsystems/FactionSubsystem/FactionSubsystem.h"

#include "Data/FactionSystem/FactionDataAsset.h"


UFactionSubsystem::UFactionSubsystem()
{
}

void UFactionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	//UE_LOG(LogTemp, Log, TEXT("Factions Subsystem Initialized"));

	InitFactions(); 
}

void UFactionSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UFactionSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}

	return false;

}

UFactionDataAsset* UFactionSubsystem::GetFactionByName_Implementation(FName Name) const
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

void UFactionSubsystem::InitFactions_Implementation()
{
	for (UFactionDataAsset* Faction : StartFactions)
	{
		RegisterFaction(Faction); 
	}
}
