// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/OptionsMenuWidget.h"

#include "Components/WidgetSwitcher.h"
#include "GameFramework/GameUserSettings.h"
#include "UI/Custom_Common/SettingsOptionRow.h"
#include "UI/Custom_Common/SettingsOptionSliderRow.h"
#include "UI/Custom_Common/UBUIWButton.h"
#include "UI/MainMenu/AudioSettingsWidget.h"
#include "UI/MainMenu/GraphicsSettings.h"

void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Audio_Button)
	{
		Audio_Button->GetMainButton()->OnClicked.AddDynamic(this, &UOptionsMenuWidget::OnAudioButtonClicked);
	}

	if (Graphics_Button)
	{
		Graphics_Button->GetMainButton()->OnClicked.AddDynamic(this, &UOptionsMenuWidget::OnGraphicsButtonClicked);
	}

	if (Back_Button)
	{
		Back_Button->GetMainButton()->OnClicked.AddDynamic(this, &UOptionsMenuWidget::OnBackButtonClicked);
	}

	if (Apply_Button)
	{
		Apply_Button->GetMainButton()->OnClicked.AddDynamic(this, &UOptionsMenuWidget::OnApplyButtonClicked);
	}
}

void UOptionsMenuWidget::OnAudioButtonClicked()
{
	WS_Settings->SetActiveWidget(WBP_AudioSettings);
}

void UOptionsMenuWidget::OnGraphicsButtonClicked()
{
	WS_Settings->SetActiveWidget(WBP_GraphicsSettings);
}

void UOptionsMenuWidget::OnBackButtonClicked()
{
	if (PrevActiveWidget)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);		
		PrevActiveWidget->SetVisibility(ESlateVisibility::Visible);		
	}
}

void UOptionsMenuWidget::OnApplyButtonClicked()
{
	if (!GEngine)
	{
		return;		
	}

	if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings())
	{
		auto MasterVolume = WBP_AudioSettings->GetOptionMasterVolum()->GetCurrentValue();
		UserSettings->SetAudioQualityLevel(MasterVolume);
		UserSettings->bUseDynamicResolution = true;
		
		//
		UserSettings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(WBP_GraphicsSettings->GetOption_WindowMode()->GetCurrentIndex()));

		//
		FText CurrentResolutionText = WBP_GraphicsSettings->GetOption_Resolution()->GetPossibleValuesText()[WBP_GraphicsSettings->GetOption_Resolution()->GetCurrentIndex()];
		auto Resol = UGeneralUtils::TextToIntPoint(CurrentResolutionText);
		UE_LOG(LogTemp, Log, TEXT("Formatted Text: %s"), *CurrentResolutionText.ToString());
		UE_LOG(LogTemp, Log, TEXT("Parsed Resolution: %d x %d"), Resol.X, Resol.Y);
		UserSettings->SetScreenResolution(Resol);

		//
		const auto VsyncValue = WBP_GraphicsSettings->GetOption_VSync()->GetCurrentIndex();
		UserSettings->SetVSyncEnabled(VsyncValue == 0? true: false);
		UE_LOG(LogTemp, Log, TEXT("Vsync Mode: %d"), static_cast<int32>(VsyncValue));

		auto ScalabilityValue = WBP_GraphicsSettings->GetOption_Scalability()->GetCurrentIndex();
		UserSettings->SetOverallScalabilityLevel(ScalabilityValue);		

		//		
		UserSettings->ApplySettings(true);
		
		
		/*// Get the current screen resolution
		FIntPoint Resolution = UserSettings->GetScreenResolution();
		UE_LOG(LogTemp, Log, TEXT("Current Resolution: %dx%d"), Resolution.X, Resolution.Y);

		// Get the fullscreen mode
		EWindowMode::Type FullscreenMode = UserSettings->GetFullscreenMode();
		UE_LOG(LogTemp, Log, TEXT("Fullscreen Mode: %d"), static_cast<int32>(FullscreenMode));
		
		// Get the graphics quality settings
		auto GraphicsQuality = UserSettings->GetOverallScalabilityLevel();
		UE_LOG(LogTemp, Log, TEXT("Graphics Quality: %d"), GraphicsQuality);*/
	}
	
}
