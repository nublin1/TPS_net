// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefenceGameMode.generated.h"

class UUpgradeBase;
class AGS_TPS;
struct FGameplayTag;

UENUM(BlueprintType)
enum class EUGameStates : uint8
{
	GameState_None,
	GameState_Gameplay,
	GameState_Shop,
	GameState_GameOver,
	GameState_Pause,
	GameState_Victory,
};

UCLASS()
class TPS_NET_API ADefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================

	//====================================================================
	// FUNCTIONS
	//====================================================================
	ADefenceGameMode();

	
	UFUNCTION()
	virtual void PostLogin(APlayerController* NewPlayer) override;
	UFUNCTION()
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	UFUNCTION()
	virtual void Logout(AController* Exiting) override;

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY()
	TObjectPtr<AGS_TPS> GameStateRef;

	UPROPERTY()
	TMap<TObjectPtr<APlayerController>, int> PlayersMoney;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDataTableRowHandle> AvaiablePlayersUpgrades;

	UPROPERTY()
	EUGameStates GameStated = EUGameStates::GameState_Gameplay;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	virtual void BeginPlay() override;
	
	

	//
	UFUNCTION()
	void InitUpgrades(APlayerController* NewPlayer);
	UFUNCTION()
	void OnPlayerStateChanged(AActor* Actor, const FGameplayTag& NewStateTag);
	UFUNCTION()
	void CheckLooseCondition();
	UFUNCTION()
	void GameOver() const;
	
	UFUNCTION()
	void ShopStateEnter();
	UFUNCTION()
	void ShopStateExit();
	
};
