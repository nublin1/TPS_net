// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DefenceGameMode.h"

#include "GS_TPS.h"
#include "Data/Upgrades/UpgradeData.h"

#include "Kismet/GameplayStatics.h"
#include "DefenceGame/Director/Director.h"
#include "GameFramework/GameStateBase.h"
#include "Player/PlayerCharacter.h"
#include "StateMachine/StateMachineComponent.h"
#include "UI/HUD/TPS/Upgrade/UpgradeBase.h"

class ADirector;

ADefenceGameMode::ADefenceGameMode()
{
}

void ADefenceGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GameStateRef = GetGameState<AGS_TPS>();
}

void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameStated = EUGameStates::GameState_Gameplay;

	auto DirectorActor = Cast<ADirector>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirector::StaticClass()));
	if (DirectorActor)
	{
		DirectorActor->OnTimerBeetweenWavesStarted.AddDynamic(this, &ADefenceGameMode::ADefenceGameMode::ShopStateEnter);
		DirectorActor->OnTimerBeetweenWavesExpired.AddDynamic(this, &ADefenceGameMode::ADefenceGameMode::ShopStateExit);
	}
}

void ADefenceGameMode::InitUpgrades(APlayerController* NewPlayer)
{
	if (AvaiablePlayersUpgrades.Num()== 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AvaiablePlayersUpgrades is Empty"));
		return;
	}

	FUpgrades ListOfPlayerUps;

	for (int i = 0; i < AvaiablePlayersUpgrades.Num(); i++)
	{
		if (AvaiablePlayersUpgrades[i].DataTable && !AvaiablePlayersUpgrades[i].RowName.IsNone())
		{
			FWeaponUpgradeRow* WData = AvaiablePlayersUpgrades[i].DataTable->FindRow<FWeaponUpgradeRow>(AvaiablePlayersUpgrades[i].RowName, AvaiablePlayersUpgrades[i].RowName.ToString());
			if (!WData)
				continue;

			auto UpgradeBaseRef = NewObject<UUpgradeBase>(this, UUpgradeBase::StaticClass());
			UpgradeBaseRef->Name = WData->Name;
			UpgradeBaseRef->SetUpgrades(WData->Upgrades);

			ListOfPlayerUps.ListOfUpgrades.Add(UpgradeBaseRef);
		}
	}

	if (ListOfPlayerUps.ListOfUpgrades.Num() > 0)
	{
		IndividualPlayerUpgrades.Add(NewPlayer, ListOfPlayerUps);
	}
}

void ADefenceGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	InitUpgrades(NewPlayer);
}

void ADefenceGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	if (!NewPlayer)
		return;

	auto PlayerCharacter = Cast<APlayerCharacter>(NewPlayer->GetPawn());
	PlayerCharacter->SetOwner(GEngine->GetFirstLocalPlayerController(GetWorld()));

	//UE_LOG(LogTemp, Log, TEXT("Owner of %s is %s"), *GetName(), *PlayerCharacter->GetOwner()->GetName());

	const auto StateMachine = PlayerCharacter->GetActiveStateCharacter();
	if (!StateMachine->StateChangedDelegate.IsAlreadyBound(this, &ADefenceGameMode::OnPlayerStateChanged))
	{
		StateMachine->StateChangedDelegate.AddDynamic(this, &ADefenceGameMode::OnPlayerStateChanged);
		GameStateRef->AlivePlayers.Add(NewPlayer);
	}

	PlayersMoney.Add(NewPlayer, 0);
}

void ADefenceGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerController* PC = Cast<APlayerController>(Exiting);
	PlayersMoney.Remove(PC);
	IndividualPlayerUpgrades.Remove(PC);
}

FUpgrades ADefenceGameMode::GetPlayerUpgrades(APlayerController* PlayerController)
{
	if (auto FoundUpgrades = IndividualPlayerUpgrades.Find(PlayerController))
	{
		return *FoundUpgrades;
	}
	
	return FUpgrades();
}

void ADefenceGameMode::OnPlayerStateChanged(AActor* Actor, const FGameplayTag& NewStateTag)
{
	auto Controller = Actor->GetInstigatorController();
	if (!Controller)
		return;

	if (!Controller->IsA(APlayerController::StaticClass()))
		return;

	auto PlayerController = Cast<APlayerController>(Controller);
	
	if (GameStateRef->AlivePlayers.Contains(PlayerController))
	{
		if (NewStateTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("State.Downed"))))
		{
			GameStateRef->AlivePlayers.Remove(PlayerController);
			GameStateRef->DeadPlayers.Add(PlayerController);
			
			//UE_LOG(LogTemp, Warning, TEXT("AlivePlayersCount %i"), AlivePlayers.Num());
			CheckLooseCondition();
		}
	}
}

void ADefenceGameMode::CheckLooseCondition()
{
	if (GameStateRef->AlivePlayers.Num() == 0)
	{
		GameStated = EUGameStates::GameState_GameOver;
		UE_LOG(LogTemp, Warning, TEXT("lose "));
		GameOver();
	}
}

void ADefenceGameMode::GameOver() const
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PC = It->Get())
		{
			PC->GameHasEnded(nullptr, false);
		}
	}
}

void ADefenceGameMode::ShopStateEnter()
{
	GameStated = EUGameStates::GameState_Shop;
}

void ADefenceGameMode::ShopStateExit()
{
	GameStated = EUGameStates::GameState_Gameplay;
}
