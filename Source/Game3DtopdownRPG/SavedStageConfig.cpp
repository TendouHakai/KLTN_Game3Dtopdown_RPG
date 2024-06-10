// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedStageConfig.h"
#include "Kismet/GameplayStatics.h"

USavedStageConfig::USavedStageConfig()
{
}

void USavedStageConfig::SaveStageCfgToFile(USavedStageConfig* Cfg)
{
	if (!Cfg) return;

	UGameplayStatics::SaveGameToSlot(Cfg, TEXT("StageData"), 0);
}

USavedStageConfig* USavedStageConfig::LoadStageCfgFromFile(bool& bSuccess)
{
	bSuccess = true;
	USavedStageConfig* TempCfg = Cast<USavedStageConfig>(UGameplayStatics::LoadGameFromSlot(TEXT("StageData"), 0));
	if (!TempCfg)
	{
		bSuccess = false;
		return Cast<USavedStageConfig>(UGameplayStatics::CreateSaveGameObject(USavedStageConfig::StaticClass()));
	}
	return TempCfg;
}
