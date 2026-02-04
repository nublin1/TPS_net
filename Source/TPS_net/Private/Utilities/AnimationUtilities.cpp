// Nublin Studio 2026 All Rights Reserved.


#include "Utilities/AnimationUtilities.h"

float UAnimationUtilities::GetSectionLengthByName(const UAnimMontage* Montage, FName SectionName)
{
	if (!Montage) return 0.f;

	int32 SectionIndex = Montage->GetSectionIndex(SectionName);
	if (SectionIndex == INDEX_NONE) return 0.f;

	float EndTime;
	float StartTime = Montage->GetAnimCompositeSection(SectionIndex).GetTime();
    
	if (Montage->CompositeSections.IsValidIndex(SectionIndex + 1))
	{
		EndTime = Montage->GetAnimCompositeSection(SectionIndex + 1).GetTime();
	}
	else
	{
		EndTime = Montage->GetPlayLength();
	}

	return EndTime - StartTime;
}

float UAnimationUtilities::GetTimeRemainingFromSection(const UAnimMontage* Montage, FName SectionName)
{
	if (!Montage) return 0.f;

	int32 SectionIndex = Montage->GetSectionIndex(SectionName);
	if (SectionIndex == INDEX_NONE) return 0.f;

	float StartTime = Montage->GetAnimCompositeSection(SectionIndex).GetTime();
	return Montage->GetPlayLength() - StartTime;
}

float UAnimationUtilities::GetTimeBetweenSections(const UAnimMontage* Montage, FName FirstSectionName,
	FName SecondSectionName)
{
	if (!Montage) return 0.f;

	int32 FirstIndex = Montage->GetSectionIndex(FirstSectionName);
	if (FirstIndex == INDEX_NONE) return 0.f;

	float StartTime = Montage->GetAnimCompositeSection(FirstIndex).GetTime();
	float EndTime = Montage->GetPlayLength(); // По умолчанию до конца

	int32 SecondIndex = Montage->GetSectionIndex(SecondSectionName);
	if (SecondIndex != INDEX_NONE)
	{
		EndTime = Montage->GetAnimCompositeSection(SecondIndex).GetTime();
	}

	// Если перепутаны местами или секции совпадают, Abs гарантирует положительное число
	return FMath::Max(0.f, EndTime - StartTime);
}

