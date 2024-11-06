// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "TPSMenuWidget.generated.h"

class UUBUIWButton;

UCLASS()
class TPS_NET_API UTPSMenuWidget :public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION(BlueprintCallable)
	void CloseWidget();

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> ResumeButton ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> ToMainMenuButton ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> QuitButton ;

	
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;
	
	//
	UFUNCTION()
	virtual void OnResumeButtonClicked();
	UFUNCTION()
	virtual void OnMainMenuButtonCliked();
	UFUNCTION()
	virtual void OnQuitButtonClicked();
};
