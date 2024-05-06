// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMgr.h"
#include "TableMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/SavedInventoryConfig.h"

void UItemMgr::Init()
{
	Super::Init();

	m_ItemArray.Empty();
	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config && true == bSuccess)
	{
		m_ItemArray = config->m_ItemArray;
	}

	//FGameItemInfo info;
	//info.m_ItemRecKey = 101;
	//info.m_ItemCount = 100;
	//info.m_ItemGrade = 1;

	//m_ItemArray.Add(info);

	//USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	//if (nullptr != config)
	//{
	//	config->m_ItemArray = this->m_ItemArray;
	//}

	//USavedInventoryConfig::SaveInventoryCfgToFile(config);
}

void UItemMgr::EndPlay()
{
	Super::EndPlay();

	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemArray = this->m_ItemArray;
	}

	USavedInventoryConfig::SaveInventoryCfgToFile(config);
}

FItemInfoRecord* UItemMgr::GetItemInfoRecord(FName Index)
{
	UDataTable* ItemInfoTable = GetMgr(UTableMgr)->ItemInfoTable;
	if (nullptr == ItemInfoTable)
		return nullptr;

	FItemInfoRecord* ItemInfoRecord = ItemInfoTable->FindRow<FItemInfoRecord>(Index, FString(""));

	if (nullptr == ItemInfoRecord) return nullptr;

	return ItemInfoRecord;
}

TArray<FGameItemInfo> UItemMgr::GetItemArray()
{
	return m_ItemArray;
}
