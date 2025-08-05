#pragma once

#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "LimbDetachmentInfo.generated.h"

USTRUCT(BlueprintType)
struct FLimbDetachmentInfo : public FTableRowBase
{
	GENERATED_BODY()

	// Имя кости, которую можно отстрелить
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BoneName;

	// Меш, который спавнится при отрыве
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> DetachedMesh;
};