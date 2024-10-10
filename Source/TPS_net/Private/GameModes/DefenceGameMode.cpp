// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DefenceGameMode.h"

#include "GS_TPS.h"
#include "GameFramework/GameStateBase.h"
#include "Player/PlayerCharacter.h"
#include "StateMachine/StateMachineComponent.h"

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
}

void ADefenceGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
}

void ADefenceGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	if (!NewPlayer)
		return;

	auto PlayerCharacter = Cast<APlayerCharacter>(NewPlayer->GetPawn());
	//PlayerCharacter->SetOwner(GEngine->GetFirstLocalPlayerController(GetWorld()));

	//UE_LOG(LogTemp, Log, TEXT("Owner of %s is %s"), *GetName(), *PlayerCharacter->GetOwner()->GetName());

	const auto StateMachine = PlayerCharacter->GetActiveStateCharacter();
	if (!StateMachine->StateChangedDelegate.IsAlreadyBound(this, &ADefenceGameMode::OnPlayerStateChanged))
	{
		StateMachine->StateChangedDelegate.AddDynamic(this, &ADefenceGameMode::OnPlayerStateChanged);
		GameStateRef->AlivePlayers.Add(NewPlayer);
	}
}

void ADefenceGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
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
		GameStated = UGameStates::GameState_GameOver;
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
