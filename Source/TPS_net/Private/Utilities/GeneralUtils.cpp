// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/GeneralUtils.h"

#include "Engine/UserInterfaceSettings.h"
#include "UObject/UnrealType.h"


EDirection UGeneralUtils::GetDirection(FVector2D Vector)
{
	float Angle = FMath::Atan2(Vector.Y, Vector.X); //Rad
	float AngleDegrees = FMath::RadiansToDegrees(Angle);

	if (AngleDegrees < 0)
	{
		AngleDegrees += 360;
	}

	// Преобразуем угол в сегмент от 0 до 7
	switch (int DirectionIndex = FMath::RoundToInt(AngleDegrees / 45.0f) % 8)
	{
	case 0:
		return EDirection::Right;
	case 1:
		return EDirection::UpRight;
	case 2:
		return EDirection::Up;
	case 3:
		return EDirection::UpLeft;
	case 4:
		return EDirection::Left;
	case 5:
		return EDirection::DownLeft;
	case 6:
		return EDirection::Down;
	case 7:
		return EDirection::DownRight;
	default:
		return EDirection::Up; 
	}
}

FString UGeneralUtils::ExpandEnumString(const FString& name, const FString& enumName)
{
	FString expanded(name);
	FString spaceLetter("");
	FString spaceNumber("");
	FString search("");
	expanded.ReplaceInline(*enumName, TEXT(""), ESearchCase::CaseSensitive);
	expanded.ReplaceInline(TEXT("::"), TEXT(""), ESearchCase::CaseSensitive);
	for (TCHAR letter = 'A'; letter <= 'Z'; ++letter)
	{
		search = FString::Printf(TEXT("%c"), letter);
		spaceLetter = FString::Printf(TEXT(" %c"), letter);
		expanded.ReplaceInline(*search, *spaceLetter, ESearchCase::CaseSensitive);
	}
	for (TCHAR number = '0'; number <= '9'; ++number)
	{
		search = FString::Printf(TEXT("%c"), number);
		spaceNumber = FString::Printf(TEXT(" %c"), number);
		expanded.ReplaceInline(*search, *spaceNumber, ESearchCase::CaseSensitive);
	}
	expanded.ReplaceInline(TEXT("_"), TEXT(" -"), ESearchCase::CaseSensitive);
	expanded = expanded.RightChop(1).TrimStartAndEnd();
	return expanded;
}

FText UGeneralUtils::ScreenResolutionRHIToText(const FScreenResolutionRHI& Resolution, bool bIgnoreRefreshRate)
{
	if (bIgnoreRefreshRate)
	{
		return FText::Format(
			NSLOCTEXT("ScreenResolution", "Format", "{0}x{1}"),
			FText::AsNumber(Resolution.Width),
			FText::AsNumber(Resolution.Height)			
		);
	}
	return FText::Format(
		NSLOCTEXT("ScreenResolution", "Format", "{0}x{1} @ {2}Hz"),
		FText::AsNumber(Resolution.Width),
		FText::AsNumber(Resolution.Height),
		FText::AsNumber(Resolution.RefreshRate)
	);
}

FText UGeneralUtils::IntPointToText(const FIntPoint Resolution)
{
	return FText::Format(
			NSLOCTEXT("ScreenResolution", "Format", "{0}x{1}"),
			FText::AsNumber(Resolution.X),
			FText::AsNumber(Resolution.Y)			
		);
}

FIntPoint UGeneralUtils::TextToIntPoint(const FText& ResolutionText)
{
	FString ResolutionString = ResolutionText.ToString();
	FIntPoint Resolution(0, 0);
	
	ResolutionString.ReplaceInline(TEXT(" "), TEXT("")); 
	ResolutionString.ReplaceInline(TEXT("\u00A0"), TEXT("")); // Удаление неразрывного пробела
	// Split the string based on the "x" delimiter
	TArray<FString> Tokens;
	ResolutionString.ParseIntoArray(Tokens, TEXT("x"), true);

	// Ensure we have exactly 2 tokens (width and height)
	if (Tokens.Num() == 2)
	{
		Tokens[0].ReplaceInline(TEXT(" "), TEXT("")); // Удаление всех пробелов
		Tokens[1].ReplaceInline(TEXT(" "), TEXT(""));
		// Convert the tokens to integers
		Resolution.X = FCString::Atoi(*Tokens[0]);
		Resolution.Y = FCString::Atoi(*Tokens[1]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid resolution format: %s"), *ResolutionString);
	}

	return Resolution;
}

FVector2D UGeneralUtils::GetViewportScaledSize()
{
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
		
	// Получение коэффициента масштабирования DPI
	const float ViewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));

	ViewportSize = ViewportSize/ViewportScale;
	//UE_LOG(LogTemp, Log, TEXT("ViewportSize: %s"), *ViewportSize.ToString());
	return ViewportSize;	
}
