// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralUtils.generated.h"


struct FScreenResolutionRHI;
/**
 * 
 */
UCLASS()
class TPS_NET_API UGeneralUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template<typename T>
	static FString EnumToString(const FString& enumName, const T value, const FString& defaultValue)
	{
		UEnum* pEnum = FindFirstObjectSafe<UEnum>(*enumName);
		return pEnum
			? ExpandEnumString(pEnum->GetNameByValue(static_cast<int64>(value)).ToString(), enumName)
			: defaultValue;
	}

	template<typename T>
	static TArray<FString> GetEnumValuesAsString(const FString& enumName)
	{
		TArray<FString> enumNames;
		UEnum* pEnum = FindFirstObjectSafe<UEnum>(*enumName);
		if (!pEnum)
		{
			return enumNames;
		}

		for (int32 i = 0; i < pEnum->GetMaxEnumValue(); ++i)
		{
			if (pEnum->IsValidEnumValue(i))
			{
				FString enumValueName = ExpandEnumString(pEnum->GetNameByValue(i).ToString(), enumName);
				enumNames.Add(enumValueName);
			}
		}
		return enumNames;
	}
	
	static FString ExpandEnumString(const FString& name, const FString& enumName);

	static FText ScreenResolutionRHIToText(const FScreenResolutionRHI& Resolution, bool bIgnoreRefreshRate);

	static FText IntPointToText(const FIntPoint Resolution);
	static FIntPoint TextToIntPoint(const FText& ResolutionText);

	UFUNCTION(BlueprintCallable)
	static FVector2D GetViewportScaledSize();
	
};
