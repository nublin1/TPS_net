// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystemHelper.generated.h"

#pragma region Enums
UENUM(BlueprintType)
enum class EAttackReadyStatus : uint8
{
	Ready                UMETA(DisplayName = "Ready to Attack"),            
	NoAmmo               UMETA(DisplayName = "Not Enough Ammo"),           
	AttackDelayActive     UMETA(DisplayName = "Attack Delay Active"),       
	WeaponNotEquipped    UMETA(DisplayName = "Weapon Not Equipped"),     
	Unknown              UMETA(DisplayName = "Unknown Reason")        
};

UENUM(Blueprintable, BlueprintType)
enum EWeaponTransitionType: uint8
{
	Holster = 0			UMETA(DisplayName = "Holster"),
	SwitchToPrimary		UMETA(DisplayName = "Switch to Primary"),
	SwitchToPistol		UMETA(DisplayName = "Switch to Pistol"),
	SwitchToUnarmed		UMETA(DisplayName = "Switch to Unarmed")
};
#pragma endregion Enums

USTRUCT(BlueprintType)
struct FAttackReadyResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	EAttackReadyStatus Status;
	
	UPROPERTY(BlueprintReadWrite)
	FString Message;
	
	FAttackReadyResult()
		: Status(EAttackReadyStatus::Unknown), Message(TEXT(""))
	{}

	explicit FAttackReadyResult(EAttackReadyStatus InStatus, const FString& InMessage = TEXT(""))
		: Status(InStatus), Message(InMessage)
	{}
};