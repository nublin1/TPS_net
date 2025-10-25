// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FootstepsData.generated.h"

/**
 * 
 */

class UNiagaraSystem;

UENUM(BlueprintType, Blueprintable)
enum class EFootstepMoveType : uint8
{
	Default = 0,
	Walk = 1,
	Run = 2,
};

/*UENUM(BlueprintType, Blueprintable)
enum class ECustomPhysicalSurface  : uint8
{
	Default = 0,
	Concreate,
	Flash,
	Asphalt
};*/

USTRUCT(BlueprintType, Blueprintable)
struct FSurfaceEffectData
{
	GENERATED_BODY()

	/** Эффект Cascade (ParticleSystem) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Effect", meta = (ToolTip = "Эффект Cascade, используемый при взаимодействии с поверхностью"))
	UParticleSystem* CascadeEffect = nullptr;

	/** Эффект Niagara */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Surface Effect", meta = (ToolTip = "Эффект Niagara, используемый при взаимодействии с поверхностью"))
	UNiagaraSystem* NiagaraEffect = nullptr;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSurfaceSoundData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceSoundData", meta = (ToolTip = "Список звуков, соответствующих каждому типу физической поверхности"))
	TMap<TEnumAsByte<EPhysicalSurface>, TObjectPtr<USoundBase>> SurfaceSounds;
};

USTRUCT(BlueprintType, Blueprintable)
struct FFootstepsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "FootstepsData")
	FName NameID;
	UPROPERTY(EditAnywhere, Category = "FootstepsData")
	EFootstepMoveType FootstepMoveType = EFootstepMoveType::Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootstepsData")
	FSurfaceSoundData SurfaceSoundData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootstepsData")
	FSurfaceEffectData SurfaceEffectData;
};

USTRUCT()
struct TPS_NET_API FFootstepsDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootstepsData")
	FFootstepsData FootstepsData;
};