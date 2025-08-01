
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

