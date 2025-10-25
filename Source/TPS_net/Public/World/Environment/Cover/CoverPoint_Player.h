// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerStructsLibrary.h"
#include "CoverPoint_Player.generated.h"

UCLASS()
class TPS_NET_API ACoverPoint_Player : public AActor
{
	GENERATED_BODY()

public:
	ACoverPoint_Player();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool StaticCoverPoint = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings",
		meta = (ToolTip =
			"Can player use front aiming while using this cover. Default cover pose has to be set to crouching to make use of it. It helps when player is in low area (vent shaft, low ceiling corridor) and can only aim sideways. To make effect, cover point can't be static (Static Cover Point = true)"
		))
	bool CanUseFrontAiming = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool LeftPeakingEnabled = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool RightPeakingEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FVector PeakLeftTriggerLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FVector PeakRightTriggerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	EStandCrouchCoverPose DefaultCoverPose = EStandCrouchCoverPose::Standing; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs")
	TObjectPtr<ACharacter> PlayerActor;
};
