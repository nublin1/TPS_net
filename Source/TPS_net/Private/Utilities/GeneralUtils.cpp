// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/GeneralUtils.h"

#include "Engine/UserInterfaceSettings.h"
#include "UObject/UnrealType.h"


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

EDirection8 UGeneralUtils::GetDirectionFromVector(const FVector2D& MovementVector)
{
	if (MovementVector.IsNearlyZero())
	{
		return EDirection8::None;
	}

	float AngleRad = FMath::Atan2(MovementVector.Y, MovementVector.X);
	float AngleDeg = FMath::RadiansToDegrees(AngleRad);

	//[0, 360]
	if (AngleDeg < 0)
	{
		AngleDeg += 360.0f;
	}

	// Каждый сектор по 45°
	if (AngleDeg >= 337.5f || AngleDeg < 22.5f)
		return EDirection8::Right;
	else if (AngleDeg < 67.5f)
		return EDirection8::UpRight;
	else if (AngleDeg < 112.5f)
		return EDirection8::Up;
	else if (AngleDeg < 157.5f)
		return EDirection8::UpLeft;
	else if (AngleDeg < 202.5f)
		return EDirection8::Left;
	else if (AngleDeg < 247.5f)
		return EDirection8::DownLeft;
	else if (AngleDeg < 292.5f)
		return EDirection8::Down;
	else // < 337.5f
		return EDirection8::DownRight;
}
