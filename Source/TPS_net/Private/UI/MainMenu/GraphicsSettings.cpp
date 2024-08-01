// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/GraphicsSettings.h"

#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "UI/Custom_Common/SettingsOptionRow.h"
#include "Utilities/GeneralUtils.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

void UGraphicsSettings::NativeConstruct()
{
	Super::NativePreConstruct();

	if (Option_WindowMode)
	{
		TArray<EWindowMode::Type> WindowModeValues = {
			EWindowMode::Fullscreen, EWindowMode::WindowedFullscreen, EWindowMode::Windowed
		};
		TArray<FText> PossibleValuesText;

		for (const auto& Value : WindowModeValues)
		{
			FString enumString = UGeneralUtils::EnumToString(TEXT("EWindowMode"), Value, TEXT("Invalid"));
			PossibleValuesText.Add(FText::FromString(enumString));
		}

		Option_WindowMode->InitializeOption(FText::FromString(TEXT("Window Mode")),
		                                    WindowModeValues.Find(ChoosenWindowMode), PossibleValuesText);
	}

	if (Option_Resolution)
	{
		if (UWorld* World = GEngine->GetCurrentPlayWorld())
		{
			TArray<FScreenResolutionRHI> Resolutions;
			UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
			TArray<FText> PossibleValuesText;
			if (RHIGetAvailableResolutions(Resolutions, true) && UserSettings)
			{
				for (const FScreenResolutionRHI& Resolution : Resolutions)
				{
					UE_LOG(LogTemp, Log, TEXT("Supported resolution: %dx%d @ %d Hz"), Resolution.Width,
					       Resolution.Height, Resolution.RefreshRate);
					PossibleValuesText.Add(UGeneralUtils::ScreenResolutionRHIToText(Resolution, true));
				}
				FIntPoint Resolution = UserSettings->GetLastConfirmedScreenResolution();
				FText CurrentResolutionText = UGeneralUtils::IntPointToText(Resolution);
				int32 CurrentResolutionIndex = PossibleValuesText.IndexOfByPredicate([&](const FText& Text)
				{
					return Text.EqualTo(CurrentResolutionText);
				});

				Option_Resolution->InitializeOption(FText::FromString(TEXT("Resolution")), CurrentResolutionIndex,
				                                    PossibleValuesText);
			}
		}
	}

	if (Option_VSync)
	{
		TArray<FText> PossibleValuesText = {FText::FromString("True"), FText::FromString("False")};
		Option_VSync->InitializeOption(FText::FromString(TEXT("VSync")), 0, PossibleValuesText);
	}
}
