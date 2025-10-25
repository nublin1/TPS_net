// Copyright Eddie Ataberk 2021 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SkinnedDecalInstance.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialLayersFunctions.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "GameFramework/SaveGame.h"
#include "SkinnedDecalSampler.generated.h"



UENUM()
enum ESkinnedDecalAdditionalData
{
	NoAdditionalData,
	SpawnTime,
	DecalBoneID,
};

UENUM()
enum ESkinnedDecalBlendMode
{
	Overlay,
	Material,
};

USTRUCT()
struct FSkinnedDecalData
{
	GENERATED_BODY()
	
	UPROPERTY(SaveGame)
	int32 Index = 0;
	
	UPROPERTY(SaveGame)
	FVector DecalLocation = FVector::ZeroVector;
	
	UPROPERTY(SaveGame)
	FVector BasisX = FVector::ZeroVector;
	
	UPROPERTY(SaveGame)
	FVector BasisY = FVector::ZeroVector;
	
	UPROPERTY(SaveGame)
	FVector BasisZ = FVector::ZeroVector;
	
	UPROPERTY(SaveGame)
	FVector Info = FVector::ZeroVector;

	FSkinnedDecalData():
	Index(0)
	{}
	
};

USTRUCT(BlueprintType)
struct FSkinnedDecalSamplerState
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	TMap<int32, FSkinnedDecalData> Decals;

	UPROPERTY(SaveGame)
	TArray<FVector> DecalLocations;

	UPROPERTY(SaveGame)
	TArray<int32> EmptyIndexes;

	UPROPERTY(SaveGame)
	int32 LastDecalIndex = -1;
};

UCLASS()
class SKINNEDDECALCOMPONENT_API USkinnedDecalSamplerSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FSkinnedDecalSamplerState SamplerState;
};

class USkinnedDecalInstance;
UCLASS(Blueprintable, BlueprintType, hidecategories = (Sockets, Collision, Object, Physics, SceneComponent, Activation, "Components|Activation", Mobility, ComponentTick), ClassGroup = Rendering, meta = (BlueprintSpawnableComponent))
class SKINNEDDECALCOMPONENT_API USkinnedDecalSampler : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkinnedDecalSampler();

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Meshes")
	USkeletalMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	int32 SpawnDecal( FVector Location, const FQuat Rotation, FName BoneName = NAME_None, float Size = 10.f, int32 SubUV = 0, int32 Index = -1);

	UFUNCTION(Category = "Skinned Decal Component")
	void SpawnDecalFromData(FSkinnedDecalData Data);

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	FSkinnedDecalSamplerState GetSamplerState();

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void SetSamplerState(FSkinnedDecalSamplerState State);
	
	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void RemoveDecal(const int32 Index = -1);

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void SetMeshComponent(USkeletalMeshComponent* MeshComponent, bool Child = false);

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void AutoSetup();
	
	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void ClearAllDecals();

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void UpdateAllDecals();
		
	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void CloneDecals(USkinnedDecalSampler* Source);

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void SaveSampler(const FString& SlotName, const int32 UserIndex);

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void LoadSampler(const FString& SlotName, const int32 UserIndex);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Performance")
	int MaxDecals = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Performance")
	float MinDecalDistance = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Blend")
	TEnumAsByte<ESkinnedDecalBlendMode> BlendMode = ESkinnedDecalBlendMode::Overlay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Blend")
	TSoftObjectPtr<UMaterialInterface> OverlayBlendMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
	int32 LayerIndex = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
	TEnumAsByte<EMaterialParameterAssociation> Association = EMaterialParameterAssociation::GlobalParameter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
	TEnumAsByte<ESkinnedDecalAdditionalData> AdditionalData = ESkinnedDecalAdditionalData::SpawnTime;
	
	UPROPERTY(BlueprintReadWrite, Category = "Material")
	TArray<UMaterialInstanceDynamic*> Materials;

	//Disabled by default for better optimization.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Save Game")
	bool EnableSaveGame = false;
	
	UFUNCTION(BlueprintPure, Category = "Skinned Decal Component")
	UTextureRenderTarget2D* GetDataTarget();

	UFUNCTION()
	void UpdateInstance(USkinnedDecalInstance* Instance);

	UPROPERTY()
	TMap<USkinnedDecalInstance*,int32> InstanceMap;

	UPROPERTY()
	UMaterialInstanceDynamic* OverlayBlendMaterialDynamic;
	
	UPROPERTY()
	TArray<USkeletalMeshComponent*> RenderMeshes;

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void SetupMaterials();

	UFUNCTION(BlueprintCallable, Category = "Skinned Decal Component")
	void SetupComponentMaterials(USkeletalMeshComponent* Component);

	UPROPERTY()
	UTextureRenderTarget2D* DataTarget;

private:
	UPROPERTY()
	FSkinnedDecalSamplerState SamplerState;
};
