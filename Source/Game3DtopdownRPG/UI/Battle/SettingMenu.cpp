// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingMenu.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "AudioDevice.h"
#include "Game3DtopdownRPG/SavedUserConfig.h"

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
	}
}

void USettingMenu::OnBackButton()
{
	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
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
