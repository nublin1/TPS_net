// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/FactionSystem/FactionAttitude.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FactionSubsystem.generated.h"

class UFactionDataAsset;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TPS_NET_API UFactionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFactionSubsystem();
	
	UFUNCTION(BlueprintCallable, Category="Factions")
	UFactionDataAsset* GetFactionByName(FName Name) const;
	UFUNCTION(BlueprintCallable, Category="Factions")
	EFactionAttitude GetAttitudeBetween(FName FactionA, FName FactionB) const;
	
	UFUNCTION(BlueprintCallable, Category="Factions")
	void RegisterFaction(UFactionDataAsset* Faction);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Factions")
	TArray<TObjectPtr<UFactionDataAsset>> AllFactions;
};
