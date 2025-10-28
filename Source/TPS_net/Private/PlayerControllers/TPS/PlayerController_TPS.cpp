// Nublin Studio 2025 All Rights Reserved.

#include "PlayerControllers/TPS/PlayerController_TPS.h"

#include "Characters/NPC/Components/AIAttackComponent.h"
#include "UI/BUIUserWidget.h"
#include "UI/HUD/Layers/MainHUDLayout.h"

APlayerController_TPS::APlayerController_TPS(): MainHUDContainer(nullptr), GameCoreHudLayout(nullptr),
                                                ChatOnScreen(nullptr)
{
}

void APlayerController_TPS::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (MainHUDLayoutWidgetClass != nullptr)
		MainHUDContainer = CreateWidget<UMainHUDLayout>(GetWorld(), MainHUDLayoutWidgetClass);
		

	if (GameOverWidgetClass != nullptr)
	{
		GameOverWidget = CreateWidget<UBUIUserWidget>(GetWorld(), GameOverWidgetClass);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameOverWidgetClass is null"));
	}
}

void APlayerController_TPS::SendMessageTo_PcGs_Implementation(FString Sender, FString Message)
{
}

void APlayerController_TPS::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if (HasAuthority())
	{
		MulticastGameHasEnded(EndGameFocus, bIsWinner);
	}
}

void APlayerController_TPS::MulticastGameHasEnded_Implementation(AActor* EndGameFocus, bool bIsWinner)
{
	if (bIsWinner)
	{
		//ShowWinScreen();
	}
	else
	{
		//ShowGameOverScreen();
		if (MainHUDContainer != nullptr)
			MainHUDContainer->SetVisibility(ESlateVisibility::Collapsed);
		if (GameOverWidget != nullptr)
		{
			GameOverWidget->AddToViewport(100);
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
			bShowMouseCursor = true; 
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameOverWidget is null"));
		}
	}
}
