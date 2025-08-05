// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Bodyparts/BodyPart.h"

#include "Components/PoseableMeshComponent.h"

ABodyPart::ABodyPart()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABodyPart::CopyBonePoseRecursive(USkeletalMeshComponent* SourceMesh, USkeletalMeshComponent* TargetMesh,
	FName StartBoneName, int32 MaxDepth, int32 CurrentDepth)
{
	if (!SourceMesh || !TargetMesh) return;

	const int32 SourceBoneIndex = SourceMesh->GetBoneIndex(StartBoneName);
	const int32 TargetBoneIndex = TargetMesh->GetBoneIndex(StartBoneName);
	
	if (SourceBoneIndex == INDEX_NONE || TargetBoneIndex == INDEX_NONE)
		return;

	// Копируем локальную трансформацию
	const FTransform& SourceLocalTransform = SourceMesh->GetBoneTransform(StartBoneName, ERelativeTransformSpace::RTS_Component);

	UPoseableMeshComponent* PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));
	PoseableMesh->SetSkinnedAsset(SourceMesh->GetSkeletalMeshAsset());
}

void ABodyPart::BeginPlay()
{
	Super::BeginPlay();
	
}