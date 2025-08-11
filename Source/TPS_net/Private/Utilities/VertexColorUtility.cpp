// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/VertexColorUtility.h"

#include "SkeletalRenderPublic.h"
#include "Rendering/SkeletalMeshRenderData.h"

TArray<FLinearColor> UVertexColorUtility::GetCurrentVertexColors(USkeletalMeshComponent* Mesh, const int32 LODIndex) 
{
	TArray<FLinearColor> Out;
	Out.SetNumUninitialized(GetVertexNum(Mesh, LODIndex));

	for(int32 i = 0; i < GetVertexNum(Mesh, LODIndex); i++)
	{
		Out[i] = GetCurrentVertexColor(Mesh, i, LODIndex);
	}

	return Out;
}

void UVertexColorUtility::SetLinearColorChannel(TArray<FLinearColor>& Colors, const float Value, const EDismemberColorChannel Channel)
{
	for(int32 i = 0; i < Colors.Num(); i++)
	{
		SetColorOfChannel(Colors[i], Value, Channel);
	}
}

void UVertexColorUtility::SetColorOfChannel(FLinearColor& Color, const float Value, const EDismemberColorChannel Channel)
{
	switch (Channel)
	{
	case EDismemberColorChannel::R_Channel:
		{
			Color.R = Value;
			return;
		}
	case EDismemberColorChannel::G_Channel:
		{
			Color.G = Value;
			return;
		}
	case EDismemberColorChannel::B_Channel:
		{
			Color.B = Value;
			return;
		}
	case EDismemberColorChannel::A_Channel:
		{
			Color.A = Value;
			return;
		}
	}
}

int32 UVertexColorUtility::GetVertexNum(USkeletalMeshComponent* InMesh, const int32 LOD)
{
	/** Dedicated Servers do not have Vertex Data */
	if(IsRunningDedicatedServer()) return 0;
	
	return InMesh->GetSkeletalMeshRenderData()->LODRenderData[LOD].GetNumVertices();
}

FLinearColor UVertexColorUtility::GetCurrentVertexColor(const USkeletalMeshComponent* Mesh, const int32 VertexIndex, const int32 LOD) 
{
	if(IsRunningDedicatedServer()) return FLinearColor(0,0,0,1);
	
	// Fail if no mesh or no color vertex buffer.
	FColor FallbackColor = FColor(255, 255, 255, 255);
	if (!Mesh->GetSkeletalMeshAsset() || !Mesh->MeshObject)
	{
		return FallbackColor.ReinterpretAsLinear();
	}

	// If there is an override, return that
	if (Mesh->LODInfo.Num() > 0 &&
		Mesh->LODInfo.IsValidIndex(LOD) &&
		Mesh->LODInfo[LOD].OverrideVertexColors != nullptr && 
		Mesh->LODInfo[LOD].OverrideVertexColors->IsInitialized() &&
		VertexIndex < (int32)Mesh->LODInfo[LOD].OverrideVertexColors->GetNumVertices() )
	{
		return Mesh->LODInfo[LOD].OverrideVertexColors->VertexColor(VertexIndex).ReinterpretAsLinear();
	}

	FSkeletalMeshLODRenderData& LODData = Mesh->MeshObject->GetSkeletalMeshRenderData().LODRenderData[LOD];
	
	if (!LODData.StaticVertexBuffers.ColorVertexBuffer.IsInitialized())
	{
		return FallbackColor.ReinterpretAsLinear();
	}

	// Find the chunk and vertex within that chunk, and skinning type, for this vertex.
	int32 SectionIndex;
	int32 VertIndex;
	LODData.GetSectionFromVertexIndex(VertexIndex, SectionIndex, VertIndex);

	check(SectionIndex < LODData.RenderSections.Num());
	const FSkelMeshRenderSection& Section = LODData.RenderSections[SectionIndex];
	
	int32 VertexBase = Section.BaseVertexIndex;

	return LODData.StaticVertexBuffers.ColorVertexBuffer.VertexColor(VertexBase + VertIndex).ReinterpretAsLinear();
}