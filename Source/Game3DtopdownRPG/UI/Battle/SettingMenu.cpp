// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingMenu.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "AudioDevice.h"
#include "Game3DtopdownRPG/SavedUserConfig.h"
#include "GameFramework/GameUserSettings.h"

void USettingMenu::CacheOwnUI()
{
	Super::CacheOwnUI();

	BackButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Back"));
	if (nullptr != BackButton)
	{
		BackButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnBackButton")));
	}

	SoundBar = GetOwnUI<UProgressBar>(TEXT("ProgressBar_SoundSFX"));
	MusicBar = GetOwnUI<UProgressBar>(TEXT("ProgressBar_SoundMusic"));
	sliderSFXBar = GetOwnUI<USlider>(TEXT("Slider_SoundSFX"));
	sliderMusicBar = GetOwnUI<USlider>(TEXT("Slider_SoundMusic"));

	if (imageSelectGraphic.Num() <= 0)
	{
		for (int i = 0; i < 4; i++)
		{
			UImage* image = GetOwnUI<UImage>(FString::Printf(TEXT("Image_GraphicSelect_%d"), i));
			if (image != nullptr)
			{
				imageSelectGraphic.Emplace(image);
			}
		}
	}

	if (imageSelectScreenSpeed.Num() <= 0)
	{
		for (int i = 0; i < 5; i++)
		{
			UImage* image = GetOwnUI<UImage>(FString::Printf(TEXT("Image_ScreenSpeedSelect_%d"), i));
			if (image != nullptr)
			{
				imageSelectScreenSpeed.Emplace(image);
			}
		}
	}

	Update();
}

bool USettingMenu::Initialize()
{
	bool Initialize = Super::Initialize();
	if (Initialize)
	{
		CacheOwnUI();
	}
	return Initialize;
}

void USettingMenu::Update()
{
	Super::Update();

	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	if (nullptr != Config)
	{
		sliderSFXBar->SetValue(Config->EffectSoundVolume);
		sliderMusicBar->SetValue(Config->BGMVolume);
		OnTapgraphicQuality(Config->IndexGraphic);
		OnTapScreenSpeed(Config->IndexScreenSpeed);
	}
}

void USettingMenu::OnBackButton()
{
	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);

	if (UIMgr != nullptr)
		UIMgr->OpenUI(EUIName::PauseMenu);
}

void USettingMenu::OnTapgraphicQuality(int index)
{
	Scalability::FQualityLevels QualityLevels;

	QualityLevels.SetFromSingleQualityLevel(index);

	Scalability::SetQualityLevels(QualityLevels, true);

	for (int i = 0; i < imageSelectGraphic.Num(); ++i)
	{
		imageSelectGraphic[i]->SetVisibility(ESlateVisibility::Hidden);
	}

	if (imageSelectGraphic.IsValidIndex(index))
	{
		imageSelectGraphic[index]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	if (nullptr != Config)
		Config->IndexGraphic = index;
	USavedUserConfig::SaveUserCfgToFile(Config);
}

void USettingMenu::OnTapScreenSpeed(int index)
{
	EMaxFps TargetFps;
	if (index == 0)
		TargetFps = EMaxFps::VeryLow;
	else if (index == 1)
		TargetFps = EMaxFps::Low;
	else if (index == 2)
		TargetFps = EMaxFps::Medium;
	else if (index == 3)
		TargetFps = EMaxFps::High;
	else
		TargetFps = EMaxFps::VeryHigh;

	GEngine->SetMaxFPS((int32)TargetFps);
	GEngine->SaveConfig();

	for (int i = 0; i < imageSelectScreenSpeed.Num(); ++i)
	{
		imageSelectScreenSpeed[i]->SetVisibility(ESlateVisibility::Hidden);
	}

	if (imageSelectScreenSpeed.IsValidIndex(index))
	{
		imageSelectScreenSpeed[index]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	if (nullptr != Config)
		Config->IndexScreenSpeed = index;
	USavedUserConfig::SaveUserCfgToFile(Config);
}

void USettingMenu::OnChangeResolution(FString resolution)
{
	bool Fullscreen = resolution == "Full Screen" ? true : false;

	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();

	if (Fullscreen)
	{
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		//UserSettings->ApplySettings(false);
		return;
	}

	FString strWidth, strHeight;
	resolution.Split(TEXT("x"), &strWidth, &strHeight);

	int Width = FCString::Atoi(*strWidth);
	int Height = FCString::Atoi(*strHeight);

	if (GEngine)
	{
		if (UserSettings)
		{
			UserSettings->SetScreenResolution(FIntPoint(Width, Height));
			UserSettings->SetFullscreenMode(EWindowMode::Windowed);
			//UserSettings->ApplySettings(false);
		}
	}

	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	if (nullptr != Config)
		Config->strResolution = resolution;
	USavedUserConfig::SaveUserCfgToFile(Config);
}

void USettingMenu::OnValueChangeSoundSFXVolume(float InValue)
{
	if (SoundBar != nullptr) SoundBar->SetPercent(InValue);
	SetSoundSFX(InValue);
}

void USettingMenu::OnValueChangeSoundMusicVolume(float InValue)
{
	if (MusicBar != nullptr) MusicBar->SetPercent(InValue);
	SetSoundMusic(InValue);
}

void USettingMenu::SetSoundSFX(float InValue)
{
	if (!GEngine) return;

	FAudioDevice* AudioDevice = GEngine->GetMainAudioDeviceRaw();
	if (!AudioDevice) return;

	for (TObjectIterator<USoundClass> It; It; ++It)
	{
		USoundClass* SoundClass = *It;
		if (SoundClass->GetName() == FString(TEXT("SFX")))
		{
			SoundClass->Properties.Volume = InValue;
		}
	}

	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	if(nullptr != Config)
		Config->EffectSoundVolume = InValue;
	USavedUserConfig::SaveUserCfgToFile(Config);
}

void USettingMenu::SetSoundMusic(float InValue)
{
	if (!GEngine) return;

	FAudioDevice* AudioDevice = GEngine->GetMainAudioDeviceRaw();
	if (!AudioDevice) return;

	for (TObjectIterator<USoundClass> It; It; ++It)
	{
		USoundClass* SoundClass = *It;
		if (SoundClass->GetName() == FString(TEXT("BGM")) ||
			SoundClass->GetName() == FString(TEXT("AMB")))
		{
			SoundClass->Properties.Volume = InValue;
		}
	}

	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	if(nullptr != Config)
		Config->BGMVolume = InValue;
	USavedUserConfig::SaveUserCfgToFile(Config);
}
