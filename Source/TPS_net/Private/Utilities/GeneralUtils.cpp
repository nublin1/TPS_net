// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/GeneralUtils.h"
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
