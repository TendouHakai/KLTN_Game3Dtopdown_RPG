// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedInventoryConfig.h"
#include "Kismet/GameplayStatics.h"

USavedInventoryConfig::USavedInventoryConfig()
{
}

void USavedInventoryConfig::SaveInventoryCfgToFile(USavedInventoryConfig* Cfg)
{
	if (!Cfg) return;

	UGameplayStatics::SaveGameToSlot(Cfg, TEXT("InventoryData"), 0);
}

USavedInventoryConfig* USavedInventoryConfig::LoadInventoryCfgFromFile(bool& bSuccess)
{
	bSuccess = true;
	USavedInventoryConfig* TempCfg = Cast<USavedInventoryConfig>(UGameplayStatics::LoadGameFromSlot(TEXT("InventoryData"), 0));
	if (!TempCfg)
	{
		bSuccess = false;
		return Cast<USavedInventoryConfig>(UGameplayStatics::CreateSaveGameObject(USavedInventoryConfig::StaticClass()));
	}
	return TempCfg;
}
