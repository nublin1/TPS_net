// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_ShowMagazine.generated.h"

UENUM(BlueprintType)
enum class EMagazineVisibilityAction : uint8
{
	Show	UMETA(DisplayName = "Show"),
	Hide	UMETA(DisplayName = "Hide")
};

UENUM(BlueprintType)
enum class EMagazineLocation : uint8
{
	InWeapon	UMETA(DisplayName = "In Weapon"),
	InHand		UMETA(DisplayName = "In Hand")
};

/**
 * AnimNotify to control magazine visibility
 */
UCLASS()
class TPS_NET_API UNotify_ShowMagazine : public UAnimNotify
{
	GENERATED_BODY()

public:
	/** What to do: show or hide */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
	EMagazineVisibilityAction Action = EMagazineVisibilityAction::Hide;

	/** Where: in weapon or in hand */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
	EMagazineLocation Location = EMagazineLocation::InWeapon;

	virtual FString GetNotifyName_Implementation() const override;
};
