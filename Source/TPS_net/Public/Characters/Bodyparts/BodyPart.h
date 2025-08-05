// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BodyPart.generated.h"

UCLASS()
class TPS_NET_API ABodyPart : public AActor
{
	GENERATED_BODY()
	
public:	
	ABodyPart();

	void CopyBonePoseRecursive(	USkeletalMeshComponent* SourceMesh,	USkeletalMeshComponent* TargetMesh,
		FName StartBoneName,	int32 MaxDepth = -1, // -1 = до конца
		int32 CurrentDepth = 0);


protected:	
	virtual void BeginPlay() override;

};
