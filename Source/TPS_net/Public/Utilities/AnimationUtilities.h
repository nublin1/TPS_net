// Nublin Studio 2026 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnimationUtilities.generated.h"

/**
 * 
 */
UCLASS()
class TPS_NET_API UAnimationUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Получаем длину конкретной секции по имени
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Animation|Montage")
	static float GetSectionLengthByName(const UAnimMontage* Montage, FName SectionName);

	// Получаем оставшееся время от начала секции до конца всего монтажа
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Animation|Montage")
	static float GetTimeRemainingFromSection(const UAnimMontage* Montage, FName SectionName);
	
	/** * Возвращает длительность между началом первой секции и началом второй секции.
	 * Если вторая секция не найдена, возвращает время от начала первой до конца монтажа.
	 */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Animation|Montage")
	static float GetTimeBetweenSections(const UAnimMontage* Montage, FName FirstSectionName, FName SecondSectionName);
};
