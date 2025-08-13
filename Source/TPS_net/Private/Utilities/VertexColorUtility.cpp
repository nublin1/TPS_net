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

void UVertexColorUtility::MaxLinearColorChannel(TArray<FLinearColor>& Colors, TArray<float>& Values, const EDismemberColorChannel Channel)
{
	for(int32 i = 0; i < Colors.Num(); i++)
	{
		MaxColorOfChannel(Colors[i], Values[i], Channel);
	}
}

void UVertexColorUtility::MaxColorOfChannel(FLinearColor& Color, float Value, EDismemberColorChannel Channel)
{
	switch (Channel)
	{
	case EDismemberColorChannel::R_Channel:
		{
			Color.R = FMath::Max(Color.R, Value);
			return;
		}
	case EDismemberColorChannel::G_Channel:
		{
			Color.G = FMath::Max(Color.G, Value);
			return;
		}
	case EDismemberColorChannel::B_Channel:
		{
			Color.B = FMath::Max(Color.B, Value);
			return;
		}
	case EDismemberColorChannel::A_Channel:
		{
			Color.A = FMath::Max(Color.A, Value);
			return;
		}
	}
}

void UVertexColorUtility::ApplyVertexColorMask(USkeletalMeshComponent* Mesh, FName BoneName, float Radius,
	float Hardness, FLinearColor Color, EDismemberColorChannel BloodVertexChannel)
{
	if (!Mesh) return;
	if (IsRunningDedicatedServer()) return;

	FVector LocalHit = FTransform(Mesh->GetSkeletalMeshAsset()->GetComposedRefPoseMatrix(BoneName)).GetLocation();

	for (int32 LOD = 0; LOD < Mesh->GetNumLODs(); LOD++)
	{
		FSkeletalMeshRenderData* RenderData = Mesh->GetSkeletalMeshAsset()->GetResourceForRendering();
		if (!RenderData) continue;

		FSkeletalMeshLODRenderData& LODData = RenderData->LODRenderData[LOD];
		FPositionVertexBuffer& Buffer = LODData.StaticVertexBuffers.PositionVertexBuffer;

		if (!Buffer.IsInitialized())
		{
			UE_LOG(LogTemp, Warning, TEXT("Vertex buffer is not initialized for LOD %d"), LOD);
			continue;
		}
		if (!Buffer.GetAllowCPUAccess())
		{
			UE_LOG(LogTemp, Warning, TEXT("Mesh does not allow CPU access! Enable 'Allow CPU Access' in the Skeletal Mesh asset."));
			continue;
		}

		FPositionVertexBuffer& PosBuffer =
            RenderData->LODRenderData[LOD]
                .StaticVertexBuffers
                .PositionVertexBuffer;
        int32 NumVerts = PosBuffer.GetNumVertices();
        if (NumVerts == 0) continue;

        // Считываем «исходные» цвета вершин
        TArray<FLinearColor> OriginalColors =
            UVertexColorUtility::GetCurrentVertexColors(Mesh, LOD);

        // Создаём рабочий массив копий
        TArray<FLinearColor> Colors = OriginalColors;
		
        TArray<float> Mask;
        Mask.Init(0.f, NumVerts);
		SphereMask(PosBuffer, LocalHit, Radius, Hardness, Mask);

		for (int32 i = 0; i < NumVerts; ++i)
		{
			SetColorOfChannel(Colors[i], Mask[i], BloodVertexChannel);
		}
		for (int32 i = 0; i < NumVerts; ++i)
		{
			float Alpha = 0.f;
			switch (BloodVertexChannel)
			{
			case EDismemberColorChannel::R_Channel: Alpha = Colors[i].R; break;
			case EDismemberColorChannel::G_Channel: Alpha = Colors[i].G; break;
			case EDismemberColorChannel::B_Channel: Alpha = Colors[i].B; break;
			case EDismemberColorChannel::A_Channel: Alpha = Colors[i].A; break;
			}

			FLinearColor Lerped = FMath::Lerp(OriginalColors[i], Color, Alpha);

			Colors[i] = Lerped;
			SetColorOfChannel(Colors[i], Alpha, BloodVertexChannel);
		}
		
		//MaxLinearColorChannel(Colors, Mask, BloodVertexChannel);
		Mesh->SetVertexColorOverride_LinearColor(LOD, Colors);
	}
}

void UVertexColorUtility::SphereMask( FPositionVertexBuffer& PosBuffer, FVector& Center, float& Radius, float& Hardness, TArray<float>& OutMask)
{
	const int32 NumVerts = PosBuffer.GetNumVertices();
	OutMask.SetNumUninitialized(NumVerts);

	for (int32 i = 0; i < NumVerts; ++i)
	{
		const FVector3f Pos3f = PosBuffer.VertexPosition(i);
		const FVector Pos = FVector(Pos3f);
		const float Dist = FVector::Dist(Pos, Center);
		
		float NormDist = FMath::Clamp(Dist / Radius, 0.f, 1.f);
		
		float RawMask = FMath::Pow(1.f - NormDist, FMath::Clamp(1.f - Hardness, 0.01f, 1.f));

		float Original = FMath::Clamp(RawMask, 0.f, 1.f);
		OutMask[i] = 1-Original;
	}
}
