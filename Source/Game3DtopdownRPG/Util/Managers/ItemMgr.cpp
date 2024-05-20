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
		m_ItemEquipmentArray = config->m_ItemEquipmentArray;
	}
}

void UItemMgr::EndPlay()
{
	Super::EndPlay();

	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemArray = this->m_ItemArray;
		config->m_ItemEquipmentArray = this->m_ItemEquipmentArray;
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

TArray<FGameItemInfo> UItemMgr::GetItemInInventoryArray()
{
	TArray<FGameItemInfo> ItemArrayInInventory;
	for (FGameItemInfo info : m_ItemArray)
	{
		if (info.m_IsInBackpack == false)
			ItemArrayInInventory.Emplace(info);
	}

	return ItemArrayInInventory;
}

TArray<FGameItemInfo> UItemMgr::GetItemInBackpackArray()
{
	TArray<FGameItemInfo> ItemArrayInInventory;
	for (FGameItemInfo info : m_ItemArray)
	{
		if (info.m_IsInBackpack == true)
			ItemArrayInInventory.Emplace(info);
	}

	return ItemArrayInInventory;
}

FString UItemMgr::GetItemGradeText(EItemGrade grade)
{
	switch (grade)
	{
	case EItemGrade::Normal:
		return FString("Normal");
	case EItemGrade::High:
		return FString("High");
	case EItemGrade::Rare:
		return FString("Rare");
	case EItemGrade::Hero:
		return FString("Hero");
	case EItemGrade::Legend:
		return FString("Legend");
	case EItemGrade::Max:
		break;
	}
	return FString("");
}

FString UItemMgr::GetDescriptionItem(const FItemInfoRecord& ItemInfoRecord)
{
	return ItemInfoRecord.Description;
}

TArray<FGameItemEquipmentInfo> UItemMgr::GetItemEquipmentInInventoryArray()
{
	TArray<FGameItemEquipmentInfo> ItemEquipArrayInInventory;
	for (FGameItemEquipmentInfo info : m_ItemEquipmentArray)
	{
		if (info.m_IsInBackpack == false)
			ItemEquipArrayInInventory.Emplace(info);
	}

	return ItemEquipArrayInInventory;
}

TArray<FGameItemEquipmentInfo> UItemMgr::GetItemEquipmentInBackpackArray()
{
	TArray<FGameItemEquipmentInfo> ItemEquipArrayInInventory;
	for (FGameItemEquipmentInfo info : m_ItemEquipmentArray)
	{
		if (info.m_IsInBackpack == true)
			ItemEquipArrayInInventory.Emplace(info);
	}

	return ItemEquipArrayInInventory;
}

FItemEquipmentInfoRecord* UItemMgr::GetItemEquipmentInfoRecord(FName Index)
{
	UDataTable* ItemEquipmentInfoTable = GetMgr(UTableMgr)->ItemEquipmentInfoTable;
	if (nullptr == ItemEquipmentInfoTable)
		return nullptr;

	FItemEquipmentInfoRecord* ItemEqupimentInfoRecord = ItemEquipmentInfoTable->FindRow<FItemEquipmentInfoRecord>(Index, FString(""));

	if (nullptr == ItemEqupimentInfoRecord) return nullptr;

	return ItemEqupimentInfoRecord;
}

FItemEquipmentInfoRecord UItemMgr::GetItemEquipmentInfoRecordBlueprint(FName Index)
{
	FItemEquipmentInfoRecord* record = GetItemEquipmentInfoRecord(Index);
	if (nullptr == record) return FItemEquipmentInfoRecord();
	return *record;
}

void UItemMgr::AddItem(int32 ItemReckey /*= 1*/, int32 ItemCount /*= 1*/, bool IsInBackpack /*= false*/)
{
	FGameItemInfo ItemInfo;
	ItemInfo.m_ItemRecKey = ItemReckey;
	ItemInfo.m_ItemCount = ItemCount;
	ItemInfo.m_IsInBackpack = IsInBackpack;

	bool bExsist = false;
	
	for (auto& info : m_ItemArray)
	{
		if (info.m_ItemRecKey == ItemInfo.m_ItemRecKey)
		{
			bExsist = true;
			info.m_ItemCount += ItemInfo.m_ItemCount;
		}
	}

	if (false == bExsist)
	{
		m_ItemArray.Emplace(ItemInfo);
	}

	// save data
	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemArray = this->m_ItemArray;
	}

	USavedInventoryConfig::SaveInventoryCfgToFile(config);
}

void UItemMgr::AddItemEquipment(int32 ItemEquipmentReckey /*= 1*/, int32 ItemUpgradeLevel /*= 1*/, bool IsInBackpack /*= false*/)
{
	FGameItemEquipmentInfo ItemInfo;
	ItemInfo.m_ItemRecKey = ItemEquipmentReckey;
	ItemInfo.m_ItemUgrapeLevel = ItemUpgradeLevel;
	ItemInfo.m_IsInBackpack = IsInBackpack;
	m_ItemEquipmentArray.Emplace(ItemInfo);

	// save data
	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemEquipmentArray = this->m_ItemEquipmentArray;
	}

	USavedInventoryConfig::SaveInventoryCfgToFile(config);
}

void UItemMgr::RemoveItem(int32 ItemReckey /*= 1*/, int32 ItemCount /*= 1*/, bool IsInBackpack /*= false*/)
{
	int indexDel = -1;
	for (int index = 0; index < m_ItemArray.Num(); ++index)
	{
		if (m_ItemArray[index].m_IsInBackpack == IsInBackpack && m_ItemArray[index].m_ItemRecKey == ItemReckey)
		{
			m_ItemArray[index].m_ItemCount -= ItemCount;
			if (m_ItemArray[index].m_ItemCount <= 0)
				indexDel = index;
			break;
		}
	}

	if(indexDel >= 0)
	{
		m_ItemArray.RemoveAt(indexDel);
	}

	// save data
	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemArray = this->m_ItemArray;
	}

	USavedInventoryConfig::SaveInventoryCfgToFile(config);
}

void UItemMgr::RemoveItemEquipment(int32 ItemReckey /*= 1*/, int32 ItemUpgradeLevel /*= 1*/, bool IsInBackpack /*= false*/)
{
	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index].m_IsInBackpack == IsInBackpack 
			&& m_ItemEquipmentArray[index].m_ItemRecKey == ItemReckey
			&& m_ItemEquipmentArray[index].m_ItemUgrapeLevel == ItemUpgradeLevel)
		{
			m_ItemEquipmentArray.RemoveAt(index);
			break;
		}
	}

	// save data
	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemEquipmentArray = this->m_ItemEquipmentArray;
	}

	USavedInventoryConfig::SaveInventoryCfgToFile(config);
}

void UItemMgr::ChangeItemEquipment(FGameItemEquipmentInfo oldItem, FGameItemEquipmentInfo newItem)
{
	newItem.m_IsInBackpack = true;
	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index] == oldItem)
		{
			m_ItemEquipmentArray[index] = newItem;
			break;
		}
	}

	// save data
	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemEquipmentArray = this->m_ItemEquipmentArray;
	}

	USavedInventoryConfig::SaveInventoryCfgToFile(config);
}
