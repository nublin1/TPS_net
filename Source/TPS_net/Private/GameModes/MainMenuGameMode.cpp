// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainMenuGameMode.h"

#include "GameInstance/MultiplayerGameInstance.h"
#include "Interfaces/OnlineIdentityInterface.h"

void AMainMenuGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnPostLogin")));
}

void AMainMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	/*if (UMultiplayerGameInstance* GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance()))
	{
		if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
		{
			IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
			if (SessionInterface.IsValid())
			{
				TSharedPtr<const FUniqueNetId> UserId = OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(NewPlayer->GetLocalPlayer()->GetControllerId());
				if (UserId.IsValid())
				{
					FName SessionName = NAME_GameSession; // или другое имя вашей сессии
					SessionInterface->RegisterPlayer(SessionName, *UserId, false);
					UE_LOG(LogTemp, Warning, TEXT("Player registered in session: %s"), *SessionName.ToString());
				}
			}
		}
	}*/
}

void AMainMenuGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	/*if (UMultiplayerGameInstance* GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance()))
	{
		const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (OnlineSubsystem)
		{
			IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
			if (SessionInterface.IsValid())
			{
				APlayerController* PlayerController = Cast<APlayerController>(Exiting);
				if (PlayerController)
				{
					TSharedPtr<const FUniqueNetId> UserId = OnlineSubsystem->GetIdentityInterface()->GetUniquePlayerId(PlayerController->GetLocalPlayer()->GetControllerId());
					if (UserId.IsValid())
					{
						FName SessionName = NAME_GameSession; // или другое имя вашей сессии
						SessionInterface->UnregisterPlayer(SessionName, *UserId);
						UE_LOG(LogTemp, Warning, TEXT("Player unregistered from session: %s"), *SessionName.ToString());
					}
				}
			}
		}
	}*/
}
