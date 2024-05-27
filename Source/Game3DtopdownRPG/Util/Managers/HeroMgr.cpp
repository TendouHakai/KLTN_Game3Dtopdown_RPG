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

void UHeroMgr::ChangeHeroParam(FCharacterParam& heroParam, const FCharacterParam& AddParam, bool IsAddParam /*= true*/)
{
	if (IsAddParam)
		heroParam += AddParam;
	else
		heroParam -= AddParam;
}
