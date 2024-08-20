// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BUIUserWidget.h"
#include "CreateLobbyWidget.generated.h"

class UCheckBox;
class UUBUIWButton;
class UEditableText;
/**
 * 
 */
UCLASS()
class TPS_NET_API UCreateLobbyWidget : public UBUIUserWidget
{
	GENERATED_BODY()

public:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	
	//====================================================================
	// FUNCTIONS
	//====================================================================

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEditableText> ServerNameText ;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCheckBox> UseLANCheckBox ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UUBUIWButton> WBP_CreateServerButton ;

	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual void NativeConstruct() override;

	//
	UFUNCTION(BlueprintCallable)
	void OnCreateServerButtonClicked();
};
