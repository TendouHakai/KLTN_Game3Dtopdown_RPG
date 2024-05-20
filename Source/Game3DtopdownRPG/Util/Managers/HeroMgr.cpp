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

	// update equip
	
	HeroInfo.m_Equip[static_cast<int32>(recordNew->EquipPosition)] = iteminfo.m_ItemRecKey;

	// udpate param
	ChangeHeroParam(HeroInfo.m_Param, recordOld->ItemEquipParam, false);
	ChangeHeroParam(HeroInfo.m_Param, recordNew->ItemEquipParam, true);

	// update Item in Backpack
	if (OldItemInfo.m_ItemRecKey == 0)
		GetMgr(UItemMgr)->RemoveItemEquipment(iteminfo.m_ItemRecKey, iteminfo.m_ItemUgrapeLevel, true);
	else
		GetMgr(UItemMgr)->ChangeItemEquipment(iteminfo, OldItemInfo);

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
