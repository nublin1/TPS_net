// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VertexColorUtility.generated.h"

#pragma region Enums

UENUM(BlueprintType)
enum class EDismemberColorChannel : uint8
{
	R_Channel UMETA(DisplayName="R"),
	G_Channel UMETA(DisplayName="G"),
	B_Channel UMETA(DisplayName="B"),
	A_Channel UMETA(DisplayName="A")
};

#pragma endregion

/**
 * 
 */
UCLASS()
class TPS_NET_API UVertexColorUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Vertex Colors")
	static TArray<FLinearColor> GetCurrentVertexColors(USkeletalMeshComponent* Mesh, const int32 LODIndex) ;
	UFUNCTION(BlueprintCallable, Category = "Vertex Colors")
	static void SetLinearColorChannel(TArray<FLinearColor>& Colors, const float Value, const EDismemberColorChannel Channel);
	UFUNCTION(BlueprintCallable, Category = "Vertex Colors")
	static void SetColorOfChannel(FLinearColor& Color, const float Value, const EDismemberColorChannel Channel);

	UFUNCTION(BlueprintCallable, Category = "Vertex Colors")
	static int32 GetVertexNum(USkeletalMeshComponent* InMesh, const int32 LOD) ;
	UFUNCTION(BlueprintCallable, Category = "Vertex Colors")
	static FLinearColor GetCurrentVertexColor(const USkeletalMeshComponent* Mesh, const int32 VertexIndex, const int32 LOD);

	
};
