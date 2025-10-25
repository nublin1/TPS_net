// Copyright Eddie Ataberk 2021 All Rights Reserved.

#include "SkinnedDecalSampler.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Engine/Canvas.h"
#include "Runtime/Launch/Resources/Version.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SkinnedMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "AnimationRuntime.h"
#include "Kismet/GameplayStatics.h"

#define PRE510 ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION < 1

USkinnedDecalSampler::USkinnedDecalSampler()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> OverlayBlendMaterialRef(TEXT("/SkinnedDecalComponent/M_SkinnedDecalOverlay"));
	if (OverlayBlendMaterialRef.Succeeded())
	{
		OverlayBlendMaterial = OverlayBlendMaterialRef.Object;
	}
	PrimaryComponentTick.bCanEverTick = false;
}

void USkinnedDecalSampler::BeginPlay()
{
	Super::BeginPlay();
}

void USkinnedDecalSampler::AutoSetup()
{
	if (!GetOwner()) return;
	
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
	GetOwner()->GetComponents<USkeletalMeshComponent>(SkeletalMeshComponents);

	Mesh = nullptr;
	
	for(USkeletalMeshComponent* Component : SkeletalMeshComponents)
	{
#if PRE510
		if(!Component->MasterPoseComponent.IsValid())
#else
		if (!Component->LeaderPoseComponent.IsValid())
#endif
		{
			SetMeshComponent(Component, false);
			break;
		}
	}
	
	if(!Mesh) return;

	for(USkeletalMeshComponent* Component : SkeletalMeshComponents)
	{
#if PRE510
		if(Component->MasterPoseComponent == Mesh)
			SetMeshComponent(Component, true);
#else
		if (Component->LeaderPoseComponent == Mesh)
			SetMeshComponent(Component, true);
#endif

	}
}


void USkinnedDecalSampler::UpdateAllDecals()
{
	TArray<UActorComponent*> InstanceComponents;
	GetOwner()->GetComponents(USkinnedDecalInstance::StaticClass(), InstanceComponents);

	for (UActorComponent* InstanceComponent : InstanceComponents)
	{
		Cast<USkinnedDecalInstance>(InstanceComponent)->UpdateDecal();
	}
}

void USkinnedDecalSampler::CloneDecals(USkinnedDecalSampler* Source)
{
	if(!Source)
	{
		return;
	}
	const FSkinnedDecalSamplerState SourceState = Source->GetSamplerState();
	SamplerState.DecalLocations = SourceState.DecalLocations;
	MaxDecals = Source->MaxDecals;
	SamplerState.EmptyIndexes = SourceState.EmptyIndexes;
	SamplerState.LastDecalIndex = SourceState.LastDecalIndex;
	DataTarget = Source->GetDataTarget(); //Cast<UTextureRenderTarget2D>(StaticDuplicateObject(Target->GetDataTarget(), Target->GetOuter()));
	Materials.Empty();
	SetupMaterials();
}

void USkinnedDecalSampler::SaveSampler(const FString& SlotName, const int32 UserIndex)
{
	USkinnedDecalSamplerSave* SamplerSave = Cast<USkinnedDecalSamplerSave>(UGameplayStatics::CreateSaveGameObject(USkinnedDecalSamplerSave::StaticClass()));
	if(!SamplerSave) return;
	SamplerSave->SamplerState = SamplerState;
	UGameplayStatics::SaveGameToSlot(SamplerSave, SlotName, 0);

}

void USkinnedDecalSampler::LoadSampler(const FString& SlotName, const int32 UserIndex)
{
	if(const USkinnedDecalSamplerSave* SamplerSave = Cast<USkinnedDecalSamplerSave>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex)))
		SetSamplerState(SamplerSave->SamplerState);
}

UTextureRenderTarget2D* USkinnedDecalSampler::GetDataTarget()
{
	if (!DataTarget)
	{
		DataTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, MaxDecals*5, 1, RTF_RGBA16f, FLinearColor::Black, false);
	}

	return DataTarget;	
}

void USkinnedDecalSampler::UpdateInstance(USkinnedDecalInstance* Instance)
{
    int32 DecalID = -1;
	if (InstanceMap.Contains(Instance))
	{
		DecalID = *InstanceMap.Find(Instance);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find the Instance Component"))
	}
	DecalID = SpawnDecal(Instance->GetComponentLocation(),Instance->GetComponentQuat(),Instance->GetAttachSocketName(),Instance->Size, Instance->SubUV, DecalID);
	InstanceMap.Add(Instance, DecalID);

}

void USkinnedDecalSampler::SetupMaterials()
{
	for (USkeletalMeshComponent* Component : RenderMeshes)
	{
		SetupComponentMaterials(Component);
	}
}

void USkinnedDecalSampler::SetupComponentMaterials(USkeletalMeshComponent* Component)
{
	switch (BlendMode)
	{
	case(Material):
		
		for(int i=0; i<Component->GetMaterials().Num(); ++i)
		{
			if(!Materials.Contains(Component->GetMaterials()[i]))
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Component->GetMaterial(i));
				if (!DynamicMaterial)
				{
					if(IsValid(Component->GetMaterial(i)))
					{
						DynamicMaterial = UMaterialInstanceDynamic::Create(Component->GetMaterial(i),GetOuter());
						Component->SetMaterial(i, DynamicMaterial);
						//Mesh->CreateDynamicMaterialInstance(i, MaterialInterfaces[i], Mesh->GetMaterialSlotNames()[i]);
					}
				}	
			
				/*if(TranslucentBlend)
				{
					if(!TranslucentBlendMaterialDynamic)
					{
						TranslucentBlendMaterialDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, TranslucentBlendMaterial);
						Materials.Add(TranslucentBlendMaterialDynamic);
					}
					DynamicMaterial = TranslucentBlendMaterialDynamic;
					Component->SetMaterial(i, DynamicMaterial);
				}
				*/
			
				if (DynamicMaterial)
				{
					DynamicMaterial->SetScalarParameterValueByInfo(FMaterialParameterInfo("DecalMax", Association, LayerIndex), MaxDecals*5);
					DynamicMaterial->SetTextureParameterValueByInfo(FMaterialParameterInfo("DecalInfo", Association, LayerIndex), GetDataTarget());
					DynamicMaterial->SetScalarParameterValueByInfo(FMaterialParameterInfo("DecalLast", Association, LayerIndex), SamplerState.DecalLocations.Num());
					Materials.Add(DynamicMaterial);
				}
			}
		}
		break;
			
	case(Overlay):
		
		if(!OverlayBlendMaterialDynamic)
		{
			OverlayBlendMaterialDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, OverlayBlendMaterial.Get());
			if (OverlayBlendMaterialDynamic)
			{
				OverlayBlendMaterialDynamic->SetScalarParameterValueByInfo(FMaterialParameterInfo("DecalMax", Association, LayerIndex), MaxDecals*5);
				OverlayBlendMaterialDynamic->SetTextureParameterValueByInfo(FMaterialParameterInfo("DecalInfo", Association, LayerIndex), GetDataTarget());
				OverlayBlendMaterialDynamic->SetScalarParameterValueByInfo(FMaterialParameterInfo("DecalLast", Association, LayerIndex), SamplerState.DecalLocations.Num());
				Materials.Add(OverlayBlendMaterialDynamic);
			}
		}
		if (OverlayBlendMaterialDynamic)
			Component->SetOverlayMaterial(OverlayBlendMaterialDynamic);
		
		break;
	}
}

void USkinnedDecalSampler::ClearAllDecals()
{
	if (DataTarget)
	{
		UKismetRenderingLibrary::ClearRenderTarget2D(this, DataTarget, FLinearColor::Black);
	}
	SamplerState.DecalLocations.Empty();
	SamplerState.LastDecalIndex = 0;
	for(int16 i=0; i<Materials.Num(); ++i)
	{
		if(IsValid(Materials[i]))
		{
			Materials[i]->SetScalarParameterValueByInfo(FMaterialParameterInfo("DecalLast", Association, LayerIndex), 0.f);
		}
	}
}

int32 USkinnedDecalSampler::SpawnDecal(FVector Location, FQuat Rotation, FName BoneName, float Size, int32 SubUV, int32 Index)
{
//	UE_LOG(LogTemp, Warning, TEXT("StartSpawnDecal"));
	FSkinnedDecalData Data;
	if(!Mesh) AutoSetup();
	if(!Mesh) return Index;

	if (!Materials.IsValidIndex(0))
	{
		SetMeshComponent(Mesh);
		if (!Materials.IsValidIndex(0))
		{
			return Index;
		}
	}

	const FTransform BoneWorldTransform = Mesh->GetSocketTransform(BoneName, RTS_World);
	const FReferenceSkeleton& RefSkeleton = Mesh->GetSkinnedAsset()->GetRefSkeleton();
	const int32 BoneIndex = Mesh->GetBoneIndex(BoneName);
	const FTransform ReferenceTransform = FAnimationRuntime::GetComponentSpaceTransformRefPose(RefSkeleton, BoneIndex);
	Data.DecalLocation = ReferenceTransform.TransformPosition(BoneWorldTransform.InverseTransformPosition(Location));

	//Check Min Decal Distance
	if(MinDecalDistance>0.f)
	{
		for (int16 i = 0; i < SamplerState.DecalLocations.Num(); ++i)
		{
			if (i == Index) continue;
			
			if ((Data.DecalLocation - SamplerState.DecalLocations[i]).SizeSquared() < MinDecalDistance)
			{
				//	UE_LOG(LogTemp, Warning, TEXT("Decals too close %f"), DistSquared);

				return Index;
			}
		}
	}
	
	const FQuat DecalRotation = ReferenceTransform.TransformRotation(BoneWorldTransform.InverseTransformRotation(Rotation));

	////////
	// Determine Decal Index
	
	Data.Index = Index;
	//	UE_LOG(LogTemp, Warning, TEXT("DecalIndexDefault: %i"), DecalIndex);
	if (Index < 0)
	{
		if(SamplerState.EmptyIndexes.IsValidIndex(0))
		{
			Data.Index = SamplerState.EmptyIndexes[0];
		}
		else
		{
			Data.Index = (SamplerState.LastDecalIndex + 1) % MaxDecals;
		}
		//	UE_LOG(LogTemp, Warning, TEXT("DecalIndexSetTo: %i"), Data.Index);
		SamplerState.LastDecalIndex = Data.Index;
	}

	if (SamplerState.DecalLocations.Num() - 1 < Data.Index)
	{
		SamplerState.DecalLocations.SetNumZeroed(Data.Index + 1);
	}
	SamplerState.DecalLocations[Data.Index] = Data.DecalLocation;

	if (!(Index < 0))
	{
		SamplerState.LastDecalIndex = SamplerState.DecalLocations.Num();
	}

	FMatrix DecalMatrix = FTransform(DecalRotation).ToMatrixNoScale();
	DecalMatrix.GetUnitAxes(Data.BasisX, Data.BasisY, Data.BasisZ);

	float AdditionalDataValue = 0;

	switch (AdditionalData)
	{
	case NoAdditionalData:
		AdditionalDataValue = 0.f;
		break;

	case SpawnTime:
		if(!GetWorld()->IsPreviewWorld())
		{
			AdditionalDataValue = GetWorld()->GetTimeSeconds();
		}
		break;

	case DecalBoneID:
		AdditionalDataValue = BoneIndex;
		break;
	}

	//	UE_LOG(LogTemp, Warning, TEXT("AddData: %f"), AdditionalDataValue);

	Data.Info = FVector(Size, SubUV, AdditionalDataValue);

	// UE_LOG(LogTemp, Warning, TEXT("SpawnDecal: %i"), DecalIndex);
	SamplerState.EmptyIndexes.Remove(Data.Index);
	
	SpawnDecalFromData(Data);
	
	if(EnableSaveGame)
	{
		SamplerState.Decals.Add(Data.Index, Data);
	}
	
	return Data.Index;
}

void USkinnedDecalSampler::SpawnDecalFromData(FSkinnedDecalData Data)
{
	if (SamplerState.DecalLocations.Num() - 1 < Data.Index)
	{
		SamplerState.DecalLocations.SetNumZeroed(Data.Index + 1);
	}
	SamplerState.DecalLocations[Data.Index] = Data.DecalLocation;
	
	UCanvas* Canvas;
	FVector2D CanvasSize;
	FDrawToRenderTargetContext RenderTargetContext;
	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, GetDataTarget(), /*out*/ Canvas, /*out*/ CanvasSize, /*out*/ RenderTargetContext);
	if(!::IsValid(Canvas)) return;
	const float DataLocation = Data.Index * 5 + 1;
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation, 0), FVector2D(DataLocation, 1), 1, FLinearColor(Data.DecalLocation));
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 1, 0), FVector2D(DataLocation + 1, 1), 1, FLinearColor(Data.BasisX));
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 2, 0), FVector2D(DataLocation + 2, 1), 1, FLinearColor(Data.BasisY));
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 3, 0), FVector2D(DataLocation + 3, 1), 1, FLinearColor(Data.BasisZ));
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 4, 0), FVector2D(DataLocation + 4, 1), 1, FLinearColor(Data.Info));
	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, RenderTargetContext);
	SamplerState.EmptyIndexes.Remove(Data.Index);

	for(int16 i=0; i<Materials.Num(); ++i)
	{
		if(!IsValid(Materials[i])) continue;
		
		Materials[i]->SetScalarParameterValueByInfo(FMaterialParameterInfo("DecalLast", Association, LayerIndex), SamplerState.DecalLocations.Num());
	}
}

FSkinnedDecalSamplerState USkinnedDecalSampler::GetSamplerState()
{
	return  SamplerState;
}

void USkinnedDecalSampler::SetSamplerState(FSkinnedDecalSamplerState State)
{
	ClearAllDecals();
	SamplerState = State;
	for(const TTuple<int32, FSkinnedDecalData>& Decal : SamplerState.Decals)
	{
		SpawnDecalFromData(Decal.Value);
	}
}

void USkinnedDecalSampler::RemoveDecal(const int32 Index)
{
	if(Index<0)	return;
	
	SamplerState.EmptyIndexes.Add(Index);
	
	UCanvas* Canvas;
	FVector2D CanvasSize;
	FDrawToRenderTargetContext RenderTargetContext;
	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, GetDataTarget(), /*out*/ Canvas, /*out*/ CanvasSize, /*out*/ RenderTargetContext);
	if(!::IsValid(Canvas))
	{
		return;
	}

	const float DataLocation = Index * 5 + 1;
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation, 0), FVector2D(DataLocation, 1), 1, FLinearColor::Black);
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 1, 0), FVector2D(DataLocation + 1, 1), 1, FLinearColor::Black);
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 2, 0), FVector2D(DataLocation + 2, 1), 1, FLinearColor::Black);
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 3, 0), FVector2D(DataLocation + 3, 1), 1, FLinearColor::Black);
	Canvas->UCanvas::K2_DrawLine(FVector2D(DataLocation + 4, 0), FVector2D(DataLocation + 4, 1), 1, FLinearColor::Black);

	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, RenderTargetContext);

	//UE_LOG(LogTemp, Warning, TEXT("RemoveDecal: %i"), Index);
}

void USkinnedDecalSampler::SetMeshComponent(USkeletalMeshComponent* MeshComponent, bool Child)
{
	if (!IsValid(MeshComponent)) return;

	if (!Child)
	{
		for (UActorComponent* Component : GetOwner()->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), "TranslucentDecalMesh"))
		{
			if (Component)
			{
				Component->DestroyComponent();
			}
		}
		Mesh = MeshComponent;
		Materials.Empty();
	}
	
	RenderMeshes.Add(MeshComponent);
	SetupComponentMaterials(MeshComponent);
	
	/*if (TranslucentBlend)
	{
		const FName MeshName = MakeUniqueObjectName(GetOuter(), USkeletalMeshComponent::StaticClass(), "DecalMesh");
		USkeletalMeshComponent* TranslucentMesh = NewObject<USkeletalMeshComponent>(GetOwner(), MeshName);
		TranslucentMesh->RegisterComponent();

		TranslucentMesh->SetSkinnedAsset(MeshComponent->GetSkinnedAsset());

		GetOwner()->AddInstanceComponent(TranslucentMesh);
		TranslucentMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

		TranslucentMesh->SetLeaderPoseComponent(MeshComponent, false);
		TranslucentMesh->BindClothToLeaderPoseComponent();

		TranslucentMesh->ComponentTags.Add("TranslucentDecalMesh");
		RenderMeshes.Add(TranslucentMesh);
	}
	else
	{
		RenderMeshes.Add(MeshComponent);
	}

	SetupComponentMaterials(MeshComponent);*/
}


