// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PCChatInterface.h"
#include "PlayerController_TPS.generated.h"

class UBUIUserWidget;
class UTPSMenuWidget;
class UChatOnScreen;
class UGameCoreHUDLayout;
class UMainHUDLayout;
/**
 * 
 */
UCLASS()
class TPS_NET_API APlayerController_TPS : public APlayerController, public IPCChatInterface
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	APlayerController_TPS();

	UFUNCTION(BlueprintCallable)
	void SendMessageTo_PcGs_Implementation(FString Sender, FString Message);

	UFUNCTION(Server, Reliable)
	void RequestHitDetectOnServer(AActor* Actor);
	UFUNCTION(Server, Reliable)
	void RequestClearAlreadyHitTargetsOnServer(AActor* Actor);

	//Getters
	UGameCoreHUDLayout* GetHUDLayout() const {return GameCoreHudLayout;}

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Classes
	UPROPERTY(EditAnywhere, Category = "HUDSettings", BlueprintReadWrite)
	TSubclassOf<UMainHUDLayout> MainHUDLayoutWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUDSettings")
	TSubclassOf<UUserWidget>GameOverWidgetClass;
	
	// Widgets
	UPROPERTY(EditAnywhere, Category = "HUDSettings", BlueprintReadWrite)
	UMainHUDLayout* MainHUDContainer;
	UPROPERTY(EditAnywhere, Category = "HUDSettings", BlueprintReadWrite)
	TObjectPtr<UGameCoreHUDLayout> GameCoreHudLayout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UChatOnScreen> ChatOnScreen;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UTPSMenuWidget> TPSMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBUIUserWidget> GameOverWidget;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void PostInitializeComponents() override;
	
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastGameHasEnded(AActor* EndGameFocus, bool bIsWinner);
};
