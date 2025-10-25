
#pragma once

#include "CoreMinimal.h"

#include "PlayerStructsLibrary.generated.h"

UENUM(BlueprintType)
enum class EDirection8 : uint8
{
	None,
	Up,
	UpRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	UpLeft
};

UENUM(BlueprintType, BlueprintType)
enum class EStandCrouchCoverPose : uint8
{
	Standing = 0,
	Crouching = 1,
};

