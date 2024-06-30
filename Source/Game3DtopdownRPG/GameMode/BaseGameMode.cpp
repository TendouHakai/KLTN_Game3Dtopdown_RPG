// Fill out your copyright notice in the Description page of Project Settings.
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"
#include "Game3DtopdownRPG/SavedUserConfig.h"
#include "AudioDevice.h"


void ABaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UIMgr = GetMgr(UUIBaseMgr);
	UIMgr->Init(this);
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitInitialUI();
	InitSoundClass();
	OnStartBGM();
}

void ABaseGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetRPGGameInstance()->EndPlayMgr();
}

void ABaseGameMode::InitInitialUI()
{
	OnInitInitialUI();
}

void ABaseGameMode::OpenReservedLevel(const FName NameLevel, const FString Options)
{
	UIMgr->CloseAllUI();
	//UGameplayStatics::OpenLevel(GetWorld(), NameLevel, false, Options);
	UGameplayStatics::OpenLevel(GetWorld(), NameLevel);
}

void ABaseGameMode::InitSoundClass()
{
	if (!GEngine) return;

	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	FAudioDevice* AudioDevice = GEngine->GetMainAudioDeviceRaw();
	if (!AudioDevice) return;

	for (TObjectIterator<USoundClass> It; It; ++It)
	{
		USoundClass* SoundClass = *It;
		FString SoundClassName = SoundClass->GetName();
		if (-1 != Config->BGMVolume &&
			(SoundClassName == FString(TEXT("BGM")) ||
				SoundClassName == FString(TEXT("AMB"))))
		{
			SoundClass->Properties.Volume = Config->BGMVolume;
		}
		else if (-1 != Config->EffectSoundVolume && SoundClassName == FString(TEXT("SFX")))
		{
			SoundClass->Properties.Volume = Config->EffectSoundVolume;
		}
	}
}
