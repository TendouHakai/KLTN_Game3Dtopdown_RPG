// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalCheatManager.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"


void UGlobalCheatManager::ItemAdd(int32 ItemReckey /*= 1*/, int32 ItemCount /*= 1*/, EInventoryLocation InventoryLocation)
{
	UItemMgr* mgr = GetMgr(UItemMgr);
	if (nullptr == mgr) return;
	mgr->AddItem(ItemReckey, ItemCount, InventoryLocation);

	// end cheat
	Endcheat();
}

void UGlobalCheatManager::ItemEquipmentAdd(int32 ItemEquipmentReckey /*= 1*/, int32 ItemUpgradeLevel /*= 1*/, EInventoryLocation InventoryLocation)
{
	UItemMgr* mgr = GetMgr(UItemMgr);
	if (nullptr == mgr) return;
	mgr->AddItemEquipment(ItemEquipmentReckey, ItemUpgradeLevel, InventoryLocation);

	// end cheat
	Endcheat();
}

void UGlobalCheatManager::Endcheat()
{
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode) return;
	GameMode->UIMgr->Update();
}
