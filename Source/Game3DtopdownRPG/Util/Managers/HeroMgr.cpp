// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroMgr.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"

void UHeroMgr::Init()
{
	Super::Init();
}

void UHeroMgr::EndPlay()
{
	Super::EndPlay();
}

void UHeroMgr::EquipHeroItem(ABaseCharacter* hero, FGameItemEquipmentInfo iteminfo)
{
	FHeroInfo HeroInfo = hero->GetHeroInfo();

	FItemEquipmentInfoRecord* recordNew = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)));
	FGameItemEquipmentInfo OldItemInfo = HeroInfo.m_Equip[static_cast<int32>(recordNew->EquipPosition)];
	FItemEquipmentInfoRecord* recordOld = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(OldItemInfo.m_ItemRecKey)));

	if (nullptr == recordNew) return;

	// udpate param
	if(nullptr != recordOld)
		ChangeHeroParam(HeroInfo.m_Param, recordOld->ItemEquipParam, false);
	ChangeHeroParam(HeroInfo.m_Param, recordNew->ItemEquipParam, true);

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
	ChangeHeroParam(HeroInfo.m_Param, record->ItemEquipParam, false);

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
