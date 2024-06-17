// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroMgr.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"
#include "Game3DtopdownRPG/Util/Managers/TableMgr.h"
#include "Game3DtopdownRPG/Util/CppFunctionLibrary.h"

void UHeroMgr::Init()
{
	Super::Init();
}

void UHeroMgr::EndPlay()
{
	Super::EndPlay();
}

FHeroRecord* UHeroMgr::GetHeroRecord(FName HeroIndex)
{
	UDataTable* HeroInfoTable = GetMgr(UTableMgr)->HeroInfoTable;
	if (nullptr == HeroInfoTable)
		return nullptr;

	FHeroRecord* HeroRecord = HeroInfoTable->FindRow<FHeroRecord>(HeroIndex, FString(""));

	if (nullptr == HeroRecord) return nullptr;

	return HeroRecord;
}

FHeroParamLevelRecord* UHeroMgr::GetHeroLevelParamRecord(FName HeroLevIndex)
{
	UDataTable* HeroLevParamTable = GetMgr(UTableMgr)->HeroLevParamTable;
	if (nullptr == HeroLevParamTable)
		return nullptr;

	FHeroParamLevelRecord* HeroParamLevelRecord = HeroLevParamTable->FindRow<FHeroParamLevelRecord>(HeroLevIndex, FString(""));

	if (nullptr == HeroParamLevelRecord) return nullptr;

	return HeroParamLevelRecord;
}

FSkillInfoRecord* UHeroMgr::GetSkillInfoRecord(FName skillIndex)
{
	UDataTable* SkillInfoTable = GetMgr(UTableMgr)->SkillInfoTable;
	if (nullptr == SkillInfoTable)
		return nullptr;

	FSkillInfoRecord* SkillInfoRecord = SkillInfoTable->FindRow<FSkillInfoRecord>(skillIndex, FString(""));

	if (nullptr == SkillInfoRecord) return nullptr;

	return SkillInfoRecord;
}

FSkillInfoRecord* UHeroMgr::GetSkillInfoRecord(EHeroClass heroclass, uint8 skillIndex)
{
		UDataTable* SkillInfoTable = GetMgr(UTableMgr)->SkillInfoTable;
	if (nullptr == SkillInfoTable)
		return nullptr;

	TArray<FSkillInfoRecord*> allrows;

	SkillInfoTable->GetAllRows(FString(), allrows);

	for (auto record : allrows)
	{
		if (record->HeroClass == heroclass && record->SkillIndex == skillIndex)
			return record;
	}

	return nullptr;
}

void UHeroMgr::LevelUpHeroParam(ABaseCharacter* hero, int32 levelup)
{
	FHeroInfo HeroInfo = hero->GetHeroInfo();

	FHeroRecord* record = GetHeroRecord(FName(FString::FromInt(hero->HeroID)));
	if (nullptr == record) return;
	FHeroParamLevelRecord* paramrecord = GetHeroLevelParamRecord(FName(FString::FromInt(record->HeroLevParamID)));
	if (nullptr == paramrecord) return;

	HeroInfo.m_Param = UCppFunctionLibrary::GetHeroParamLevel(HeroInfo.m_Param, paramrecord->ParamUpgrape, levelup);

	hero->SetHeroInfo(HeroInfo);
	// update UI
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode) return;
	GameMode->UIMgr->Update();
}

void UHeroMgr::LevelUpItemEquipmentHeroParam(ABaseCharacter* hero, FGameItemEquipmentInfo info)
{
	if (info.m_ItemRecKey == 0) return;
	if (info.m_InventoryLocation != EInventoryLocation::InEquipment) return;

	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(info.m_ItemRecKey)));
	if (record == nullptr) return;

	FHeroInfo HeroInfo = hero->GetHeroInfo();

	UnEquipHeroItem(hero, HeroInfo.m_Equip[(int32)record->EquipPosition]);
	EquipHeroItem(hero, info);
}

void UHeroMgr::EquipHeroItem(ABaseCharacter* hero, FGameItemEquipmentInfo iteminfo)
{
	FHeroInfo HeroInfo = hero->GetHeroInfo();

	FItemEquipmentInfoRecord* recordNew = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)));
	FGameItemEquipmentInfo OldItemInfo = HeroInfo.m_Equip[static_cast<int32>(recordNew->EquipPosition)];
	FItemEquipmentInfoRecord* recordOld = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(OldItemInfo.m_ItemRecKey)));

	if (nullptr == recordNew) return;

	// udpate param
	FCharacterParam tempParam;
	if (nullptr != recordOld)
	{
		tempParam = recordOld->ItemEquipParam;
		if (OldItemInfo.m_ItemUgrapeLevel >= 1)
		{
			FItemParamLevRecord* levelParam = GetMgr(UItemMgr)->GetItemParamLevRecord(FName(FString::FromInt(recordOld->ItemParamLevID)));
			if (levelParam != nullptr)
				tempParam = UCppFunctionLibrary::GetHeroParamLevel(recordOld->ItemEquipParam, levelParam->ParamUpgrade, iteminfo.m_ItemUgrapeLevel);
		}
		ChangeHeroParam(HeroInfo.m_Param, tempParam, false);
	}
		
	tempParam = recordNew->ItemEquipParam;
	if (iteminfo.m_ItemUgrapeLevel >= 1)
	{
		FItemParamLevRecord* levelParam = GetMgr(UItemMgr)->GetItemParamLevRecord(FName(FString::FromInt(recordNew->ItemParamLevID)));
		if (levelParam != nullptr)
			tempParam = UCppFunctionLibrary::GetHeroParamLevel(recordNew->ItemEquipParam, levelParam->ParamUpgrade, iteminfo.m_ItemUgrapeLevel);
	}
	ChangeHeroParam(HeroInfo.m_Param, tempParam, true);

	// update Item in Backpack
	if (OldItemInfo.m_ItemRecKey == 0)
		GetMgr(UItemMgr)->ChangeItemEquipmentInventoryLocation(iteminfo, EInventoryLocation::InEquipment);
	else
	{
		GetMgr(UItemMgr)->ChangeItemEquipmentInventoryLocation(iteminfo, EInventoryLocation::InEquipment);
		GetMgr(UItemMgr)->ChangeItemEquipmentInventoryLocation(OldItemInfo, EInventoryLocation::InBackpack);
	}

	// update equip
	iteminfo.m_InventoryLocation = EInventoryLocation::InEquipment;
	HeroInfo.m_Equip[static_cast<int32>(recordNew->EquipPosition)] = iteminfo;

	hero->SetHeroInfo(HeroInfo);

	// update UI
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode) return;
	GameMode->UIMgr->Update();
}

void UHeroMgr::UnEquipHeroItem(ABaseCharacter* hero, FGameItemEquipmentInfo iteminfo)
{
	FHeroInfo HeroInfo = hero->GetHeroInfo();

	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)));
	if (nullptr == record) return;

	// update param
	FCharacterParam tempParam;
	tempParam = record->ItemEquipParam;
	if (iteminfo.m_ItemUgrapeLevel >= 1)
	{
		FItemParamLevRecord* levelParam = GetMgr(UItemMgr)->GetItemParamLevRecord(FName(FString::FromInt(record->ItemParamLevID)));
		if(levelParam != nullptr)
			tempParam = UCppFunctionLibrary::GetHeroParamLevel(record->ItemEquipParam, levelParam->ParamUpgrade, iteminfo.m_ItemUgrapeLevel);
	}
	ChangeHeroParam(HeroInfo.m_Param, tempParam, false);

	// update Item Mgr
	GetMgr(UItemMgr)->ChangeItemEquipmentInventoryLocation(iteminfo, EInventoryLocation::InBackpack);

	// update equip
	HeroInfo.m_Equip[static_cast<int32>(record->EquipPosition)] = FGameItemEquipmentInfo();

	hero->SetHeroInfo(HeroInfo);

	// update UI
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode) return;
	GameMode->UIMgr->Update();
}

void UHeroMgr::UnEquipHeroItemByClass(ABaseCharacter* hero)
{
	if (nullptr == hero) return;

	FHeroInfo HeroInfo = hero->GetHeroInfo();

	for (int equipIndex = 0; equipIndex < HeroInfo.m_Equip.Num(); ++equipIndex)
	{
		if (HeroInfo.m_Equip[equipIndex].m_ItemRecKey == 0) continue;
		FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(HeroInfo.m_Equip[equipIndex].m_ItemRecKey)));
		if (nullptr == record) continue;
		if (record->EquipPosition == EItemEquipPosition::Weapon) continue;
		if (record->EquipPosition == EItemEquipPosition::All) continue;

		if (record->HeroClass != hero->GetCurrentHeroClass())
		{
			hero->UnEquipItem(HeroInfo.m_Equip[equipIndex]);
		}
	}
}

void UHeroMgr::EquipHeroNormalItem(ABaseCharacter* hero, FGameItemInfo iteminfo, int32 position)
{
	if (iteminfo.m_InventoryLocation == EInventoryLocation::InEquipment) return;
	FHeroInfo HeroInfo = hero->GetHeroInfo();

	FGameItemInfo OldItemInfo = HeroInfo.m_EquipNormal[position];

	// update Item in Backpack
	if (OldItemInfo.m_ItemRecKey == 0)
		GetMgr(UItemMgr)->ChangeItemInventoryLocation(iteminfo, iteminfo.m_ItemCount, EInventoryLocation::InEquipment);
	else
	{
		GetMgr(UItemMgr)->ChangeItemInventoryLocation(iteminfo, iteminfo.m_ItemCount, EInventoryLocation::InEquipment);
		GetMgr(UItemMgr)->ChangeItemInventoryLocation(OldItemInfo, OldItemInfo.m_ItemCount, EInventoryLocation::InBackpack);
	}

	// update equip
	iteminfo.m_InventoryLocation = EInventoryLocation::InEquipment;
	HeroInfo.m_EquipNormal[position] = iteminfo;

	hero->SetHeroInfo(HeroInfo);

	// update UI
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode) return;
	GameMode->UIMgr->Update();
}

void UHeroMgr::UnEquipHeroNormalItem(ABaseCharacter* hero, FGameItemInfo iteminfo, int32 position)
{
	FHeroInfo HeroInfo = hero->GetHeroInfo();

	// update Item Mgr
	GetMgr(UItemMgr)->ChangeItemInventoryLocation(iteminfo, iteminfo.m_ItemCount, EInventoryLocation::InBackpack);

	// update equip
	HeroInfo.m_EquipNormal[position] = FGameItemInfo();

	hero->SetHeroInfo(HeroInfo);

	// update UI
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode) return;
	GameMode->UIMgr->Update();
}

void UHeroMgr::UseEquipHeroNormalItem(ABaseCharacter* hero, int32 position)
{
	FHeroInfo HeroInfo = hero->GetHeroInfo();
	FGameItemInfo iteminfo = HeroInfo.m_EquipNormal[position];

	// update Item Mgr
	GetMgr(UItemMgr)->RemoveItem(iteminfo.m_ItemRecKey, 1, EInventoryLocation::InEquipment);

	// update equip
	HeroInfo.m_EquipNormal[position].m_ItemCount -= 1;
	if (HeroInfo.m_EquipNormal[position].m_ItemCount <= 0)
	{
		HeroInfo.m_EquipNormal[position] = FGameItemInfo();
	}

	hero->SetHeroInfo(HeroInfo);

	// update UI
	ABaseGameMode* GameMode = GetGameModeAs(ABaseGameMode);
	if (nullptr == GameMode) return;
	GameMode->UIMgr->Update();
}

void UHeroMgr::ChangeHeroParam(FCharacterParam& heroParam, const FCharacterParam& AddParam, bool IsAddParam /*= true*/)
{
	if (IsAddParam)
		heroParam += AddParam;
	else
		heroParam -= AddParam;
}
