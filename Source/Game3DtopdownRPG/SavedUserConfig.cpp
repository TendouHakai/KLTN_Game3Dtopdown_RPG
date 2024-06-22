// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedUserConfig.h"
#include "Kismet/GameplayStatics.h"

USavedUserConfig::USavedUserConfig()
{
	BGMVolume = 1.0f;
	EffectSoundVolume = 1.0f;
}

void USavedUserConfig::SaveUserCfgToFile(USavedUserConfig* Cfg)
{
	if (!Cfg) return;

	UGameplayStatics::SaveGameToSlot(Cfg, TEXT("CommonSaveData"), 0);
}

USavedUserConfig* USavedUserConfig::LoadUserCfgFromFile(bool& bSuccess)
{
	bSuccess = true;
	USavedUserConfig* TempCfg = Cast<USavedUserConfig>(UGameplayStatics::LoadGameFromSlot(TEXT("CommonSaveData"), 0));
	if (!TempCfg)
	{
		bSuccess = false;
		return Cast<USavedUserConfig>(UGameplayStatics::CreateSaveGameObject(USavedUserConfig::StaticClass()));
	}
	return TempCfg;
}

void USavedUserConfig::InitUserCfgFile()
{

}
