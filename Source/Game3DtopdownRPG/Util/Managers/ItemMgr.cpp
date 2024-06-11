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
		Gold = config->Gold;
		Energy = config->Energy;
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
		config->Gold = Gold;
		config->Energy = Energy;
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

FItemEquipmentInfoRecord* UItemMgr::GetItemEquipmentInfoRecord(FName Index)
{
	UDataTable* ItemEquipmentInfoTable = GetMgr(UTableMgr)->ItemEquipmentInfoTable;
	if (nullptr == ItemEquipmentInfoTable)
		return nullptr;

	FItemEquipmentInfoRecord* ItemEqupimentInfoRecord = ItemEquipmentInfoTable->FindRow<FItemEquipmentInfoRecord>(Index, FString(""));

	if (nullptr == ItemEqupimentInfoRecord) return nullptr;

	return ItemEqupimentInfoRecord;
}

FItemEquipmentLevRecord* UItemMgr::GetItemEquipmentLevelRecord(FName Index)
{
	UDataTable* ItemEquipmentLevInfoTable = GetMgr(UTableMgr)->ItemEquipmentLevInfoTable;
	if (nullptr == ItemEquipmentLevInfoTable)
		return nullptr;

	FItemEquipmentLevRecord* ItemEquipmentLevRecord = ItemEquipmentLevInfoTable->FindRow<FItemEquipmentLevRecord>(Index, FString(""));

	if (nullptr == ItemEquipmentLevRecord) return nullptr;

	return ItemEquipmentLevRecord;
}

FUpgradeLevelOfMaterialRecord* UItemMgr::GetUpgradeLevelOfMaterialRecord(FName Index)
{
	UDataTable* UpgradeLevelOfMaterialTable = GetMgr(UTableMgr)->UpgradeLevelOfMaterialTable;
	if (nullptr == UpgradeLevelOfMaterialTable)
		return nullptr;

	FUpgradeLevelOfMaterialRecord* UpgradeLevelOfMaterialRecord = UpgradeLevelOfMaterialTable->FindRow<FUpgradeLevelOfMaterialRecord>(Index, FString(""));

	if (nullptr == UpgradeLevelOfMaterialRecord) return nullptr;

	return UpgradeLevelOfMaterialRecord;
}

FItemParamLevRecord* UItemMgr::GetItemParamLevRecord(FName Index)
{
	UDataTable* ItemParamLevTable = GetMgr(UTableMgr)->ItemParamLevTable;
	if (nullptr == ItemParamLevTable)
		return nullptr;

	FItemParamLevRecord* ItemParamLevRecord = ItemParamLevTable->FindRow<FItemParamLevRecord>(Index, FString(""));

	if (nullptr == ItemParamLevRecord) return nullptr;

	return ItemParamLevRecord;
}

FExpForGradeRecord* UItemMgr::GetExpForGradeRecord(FName Index)
{
	UDataTable* ExpForItemGradeTable = GetMgr(UTableMgr)->ExpForItemGradeTable;
	if (nullptr == ExpForItemGradeTable)
		return nullptr;

	FExpForGradeRecord* ExpForGradeRecord = ExpForItemGradeTable->FindRow<FExpForGradeRecord>(Index, FString(""));

	if (nullptr == ExpForGradeRecord) return nullptr;

	return ExpForGradeRecord;
}

FItemTypeInfoRecord* UItemMgr::GetItemTypeInfoRecord(FName Index)
{
	UDataTable* ItemTypeInfoTable = GetMgr(UTableMgr)->ItemTypeInfoTable;
	if (nullptr == ItemTypeInfoTable)
		return nullptr;

	FItemTypeInfoRecord* ItemTypeInfoRecord = ItemTypeInfoTable->FindRow<FItemTypeInfoRecord>(Index, FString(""));

	if (nullptr == ItemTypeInfoRecord) return nullptr;

	return ItemTypeInfoRecord;
}

TArray<FGameItemInfo> UItemMgr::GetAllItemRecipeByItemType(EItemType type)
{
	TArray<FGameItemInfo> array;

	UDataTable* ItemInfoTable = GetMgr(UTableMgr)->ItemInfoTable;
	if (nullptr == ItemInfoTable) return array;

	TArray<FItemInfoRecord*> allrows;

	ItemInfoTable->GetAllRows(FString(), allrows);

	for (int index = 0; index < allrows.Num(); ++index)
	{
		if(allrows[index]->CanMake == true && allrows[index]->ItemType == type)
			array.Emplace(FGameItemInfo(0, allrows[index]->ItemReckey));
	}

	return array;
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
		if (info.m_InventoryLocation == EInventoryLocation::InInventory)
			ItemArrayInInventory.Emplace(info);
	}

	return ItemArrayInInventory;
}

TArray<FGameItemInfo> UItemMgr::GetItemInBackpackArray()
{
	TArray<FGameItemInfo> ItemArrayInInventory;
	for (FGameItemInfo info : m_ItemArray)
	{
		if (info.m_InventoryLocation == EInventoryLocation::InBackpack)
			ItemArrayInInventory.Emplace(info);
	}

	return ItemArrayInInventory;
}

TArray<FGameItemInfo> UItemMgr::GetItemArrayByItemType(EItemType type, EInventoryLocation location)
{
	TArray<FGameItemInfo> ItemArrayByItemType;
	for (FGameItemInfo info : m_ItemArray)
	{
		FItemInfoRecord* record = GetItemInfoRecord(FName(FString::FromInt(info.m_ItemRecKey)));
		if (nullptr == record) continue;
		if (record->ItemType == type && (info.m_InventoryLocation == location || location == EInventoryLocation::All))
			ItemArrayByItemType.Emplace(info);
	}

	return ItemArrayByItemType;
}

TArray<FGameItemInfo> UItemMgr::GetItemArrayByCategory(EItemCategory category, EInventoryLocation location)
{
	TArray<FGameItemInfo> ItemArrayByItemType;
	for (FGameItemInfo info : m_ItemArray)
	{
		FItemInfoRecord* record = GetItemInfoRecord(FName(FString::FromInt(info.m_ItemRecKey)));
		if (nullptr == record) continue;
		if (record->Category == category && info.m_InventoryLocation == location)
			ItemArrayByItemType.Emplace(info);
	}

	return ItemArrayByItemType;
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
		if (info.m_InventoryLocation == EInventoryLocation::InInventory)
			ItemEquipArrayInInventory.Emplace(info);
	}

	return ItemEquipArrayInInventory;
}

TArray<FGameItemEquipmentInfo> UItemMgr::GetItemEquipmentInBackpackArray()
{
	TArray<FGameItemEquipmentInfo> ItemEquipArrayInInventory;
	for (FGameItemEquipmentInfo info : m_ItemEquipmentArray)
	{
		if (info.m_InventoryLocation == EInventoryLocation::InBackpack)
			ItemEquipArrayInInventory.Emplace(info);
	}

	return ItemEquipArrayInInventory;
}

TArray<FGameItemEquipmentInfo> UItemMgr::GetItemEquipmentArrayByEquipPosition(EItemEquipPosition position, EInventoryLocation location)
{
	TArray<FGameItemEquipmentInfo> ItemEquipArrayInInventory;
	for (FGameItemEquipmentInfo info : m_ItemEquipmentArray)
	{
		if (info.m_InventoryLocation == location)
		{
			FItemEquipmentInfoRecord* record = GetItemEquipmentInfoRecord(FName(FString::FromInt(info.m_ItemRecKey)));
			if(nullptr == record) continue;
			if(record->EquipPosition == position)
				ItemEquipArrayInInventory.Emplace(info);
		}
	}

	return ItemEquipArrayInInventory;
}

FItemEquipmentInfoRecord UItemMgr::GetItemEquipmentInfoRecordBlueprint(FName Index)
{
	FItemEquipmentInfoRecord* record = GetItemEquipmentInfoRecord(Index);
	if (nullptr == record) return FItemEquipmentInfoRecord();
	return *record;
}

TArray<FGameItemEquipmentInfo> UItemMgr::GetAllItemEquipmentRecipe()
{
	TArray<FGameItemEquipmentInfo> array;

	UDataTable* ItemEquipmentInfoTable = GetMgr(UTableMgr)->ItemEquipmentInfoTable;
	if (nullptr == ItemEquipmentInfoTable) return array;

	TArray<FItemEquipmentInfoRecord*> allrows;

	ItemEquipmentInfoTable->GetAllRows(FString(), allrows);

	for (int index = 0; index < allrows.Num(); ++index)
	{
		array.Emplace(FGameItemEquipmentInfo(index+1));
	}

	return array;
}

EResult UItemMgr::ForgingItemEquipment(int32 ItemReckey, int32 count, int32& errorcode)
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(ItemReckey)));
	// check
	if (nullptr == record)
	{
		errorcode = 0;
		return EResult::Fail;
	}

	for (int matIndex = 0; matIndex < record->Materials.Num(); ++matIndex)
	{
		FGameItemInfo info = GetMgr(UItemMgr)->FindItem(record->Materials[matIndex]);
		if (info.m_ItemCount < record->MatCounts[matIndex]*count)
		{
			errorcode = 1;
			return EResult::Fail;
		}
	}

	int32 countitem = GetMgr(UItemMgr)->CountItemEqupiment(record->PreviousItem);
	if (countitem < count)
	{
		errorcode = 2;
		return EResult::Fail;
	}

	// xu ly
	for (int matIndex = 0; matIndex < record->Materials.Num(); ++matIndex)
	{
		RemoveItem(record->Materials[matIndex], record->MatCounts[matIndex], EInventoryLocation::All);
	}

	for (int i = 0; i < count; ++i)
	{
		FGameItemEquipmentInfo info = FindItemEquipmentWorstStat(record->PreviousItem);
		RemoveItemEquipment(info);
	}

	AddItemEquipment(ItemReckey, 1, EInventoryLocation::InBackpack);

	return EResult::Success;
}

EResult UItemMgr::MakeItem(int32 ItemReckey, int32 count, int32& errorcode)
{
	if (count == 0)
	{
		errorcode = 0;
		return EResult::Fail;
	}
	
	// check 
	FItemInfoRecord* record = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(ItemReckey)));
	if (nullptr == record)
	{
		errorcode = 1;
		return EResult::Fail;
	}

	for (int matIndex = 0; matIndex < record->Materials.Num(); ++matIndex)
	{
		FGameItemInfo info = GetMgr(UItemMgr)->FindItem(record->Materials[matIndex]);
		if (info.m_ItemCount < record->MatCounts[matIndex] * count)
		{
			errorcode = 2;
			return EResult::Fail;
		}
	}

	// excute
	for (int matIndex = 0; matIndex < record->Materials.Num(); ++matIndex)
	{
		RemoveItem(record->Materials[matIndex], record->MatCounts[matIndex] * count, EInventoryLocation::All);
	}

	AddItem(ItemReckey, count, EInventoryLocation::InBackpack);

	return EResult::Success;
}

FItemEquipmentLevRecord* UItemMgr::GetItemEquipmentLevelRecordByTotalExp(int32 totalExp)
{
	UDataTable* ItemEquipmentLevInfoTable = GetMgr(UTableMgr)->ItemEquipmentLevInfoTable;
	if (nullptr == ItemEquipmentLevInfoTable)
		return nullptr;

	TArray<FItemEquipmentLevRecord*> allrows;

	ItemEquipmentLevInfoTable->GetAllRows(FString(), allrows);

	for (auto record : allrows)
	{
		if (totalExp <= record->expEnd && totalExp >= record->expStart)
			return record;
	}

	return nullptr;
}

void UItemMgr::AddItem(int32 ItemReckey /*= 1*/, int32 ItemCount /*= 1*/, EInventoryLocation InventoryLocation /*= EInventoryLocation::InInventory*/)
{
	FItemInfoRecord* record = GetItemInfoRecord(FName(FString::FromInt(ItemReckey)));
	if (nullptr == record) return;

	FGameItemInfo ItemInfo;
	ItemInfo.m_ItemRecKey = ItemReckey;
	ItemInfo.m_ItemCount = ItemCount;
	ItemInfo.m_InventoryLocation = InventoryLocation;

	bool bExsist = false;
	
	for (auto& info : m_ItemArray)
	{
		if (info.m_ItemRecKey == ItemInfo.m_ItemRecKey  && info.m_InventoryLocation == ItemInfo.m_InventoryLocation)
		{
			bExsist = true;
			info.m_ItemCount += ItemInfo.m_ItemCount;
			break;
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

void UItemMgr::RemoveItem(int32 ItemReckey, int32 ItemCount, EInventoryLocation InventoryLocation)
{
	TArray<int32> indexRemoves;

	for (int index = 0; index < m_ItemArray.Num(); ++index)
	{
		if (m_ItemArray[index].m_ItemRecKey == ItemReckey && (m_ItemArray[index].m_InventoryLocation == InventoryLocation || InventoryLocation == EInventoryLocation::All))
		{
			m_ItemArray[index].m_ItemCount -= ItemCount;
			if (m_ItemArray[index].m_ItemCount <= 0)
			{
				indexRemoves.Emplace(index);
				if (m_ItemArray[index].m_ItemCount < 0)
				{
					ItemCount = FMath::Abs(m_ItemArray[index].m_ItemCount);
					break;
				}
			}
		}
	}

	for (int index = 0; index < indexRemoves.Num(); ++index)
	{
		m_ItemArray.RemoveAt(indexRemoves[index]);
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

void UItemMgr::AddItemEquipment(int32 ItemEquipmentReckey /*= 1*/, int32 ItemUpgradeLevel /*= 1*/, EInventoryLocation InventoryLocation /*= EInventoryLocation::InInventory*/)
{
	FItemEquipmentInfoRecord* record = GetItemEquipmentInfoRecord(FName(FString::FromInt(ItemEquipmentReckey)));
	FItemEquipmentLevRecord* levRecord = GetItemEquipmentLevelRecord(FName(FString::FromInt(ItemUpgradeLevel)));
	if (nullptr == record) return;
	if (nullptr == levRecord) return;

	FGameItemEquipmentInfo ItemInfo;
	ItemInfo.m_ItemRecKey = ItemEquipmentReckey;
	ItemInfo.m_ItemUgrapeLevel = ItemUpgradeLevel;
	ItemInfo.m_ItemUgrapeExp = levRecord->expStart;
	ItemInfo.m_InventoryLocation = InventoryLocation;
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

void UItemMgr::RemoveItemEquipment(FGameItemEquipmentInfo iteminfo)
{
	int indexRemove = -1;

	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index] == iteminfo)
		{
			indexRemove = index;
			break;
		}
	}

	if (indexRemove >= 0) m_ItemEquipmentArray.RemoveAt(indexRemove);

	// save data
	bool bSuccess = true;
	USavedInventoryConfig* config = USavedInventoryConfig::LoadInventoryCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_ItemEquipmentArray = this->m_ItemEquipmentArray;
	}

	USavedInventoryConfig::SaveInventoryCfgToFile(config);
}

void UItemMgr::ChangeItemInventoryLocation(FGameItemInfo iteminfo, int ItemCount, EInventoryLocation Inventorylocation)
{
	for (int index = 0; index < m_ItemArray.Num(); ++index)
	{
		if (m_ItemArray[index].m_ItemRecKey == iteminfo.m_ItemRecKey && m_ItemArray[index].m_ItemCount == iteminfo.m_ItemCount && m_ItemArray[index].m_InventoryLocation == iteminfo.m_InventoryLocation)
		{
			if (m_ItemArray[index].m_ItemCount < ItemCount)
			{
				FGameItemInfo info;
				info.m_ItemRecKey = m_ItemArray[index].m_ItemRecKey;
				info.m_ItemCount = ItemCount;
				info.m_InventoryLocation = Inventorylocation;

				m_ItemArray.Emplace(info);
			}
			else
			{
				m_ItemArray[index].m_InventoryLocation = Inventorylocation;
			}
			break;
		}
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

void UItemMgr::ChangeItemEquipmentInventoryLocation(FGameItemEquipmentInfo iteminfo, EInventoryLocation Inventorylocation)
{
	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index] == iteminfo)
		{
			m_ItemEquipmentArray[index].m_InventoryLocation = Inventorylocation;
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

FGameItemEquipmentInfo UItemMgr::UpgradeLevelItemEquipment(FGameItemEquipmentInfo iteminfo, TArray<FGameItemInfo> Materials)
{
	FGameItemEquipmentInfo newinfo;

	if (iteminfo.m_ItemRecKey == 0) return newinfo;
	if (Materials.Num() == 0) return newinfo;

	int32 UpgradeExp = 0;

	// Remove materials

	for (int index = 0; index < Materials.Num(); ++index)
	{
		FUpgradeLevelOfMaterialRecord* UpgradeRecord = GetMgr(UItemMgr)->GetUpgradeLevelOfMaterialRecord(FName(FString::FromInt(Materials[index].m_ItemRecKey)));
		RemoveItem(Materials[index].m_ItemRecKey, Materials[index].m_ItemCount, Materials[index].m_InventoryLocation);
		UpgradeExp += (UpgradeRecord->expUpgrade * Materials[index].m_ItemCount);
	}

	// Update level item

	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index] == iteminfo)
		{
			m_ItemEquipmentArray[index].m_ItemUgrapeExp += UpgradeExp;
			FItemEquipmentLevRecord* levRecord = GetItemEquipmentLevelRecordByTotalExp(m_ItemEquipmentArray[index].m_ItemUgrapeExp);
			m_ItemEquipmentArray[index].m_ItemUgrapeLevel = levRecord->Level;
			newinfo = m_ItemEquipmentArray[index];
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

	return newinfo;
}

bool UItemMgr::isHaveEquipmentItem(FGameItemEquipmentInfo iteminfo)
{
	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index] == iteminfo)
		{
			return true;
		}
	}

	return false;
}

FGameItemInfo UItemMgr::FindItem(int32 ItemReckey)
{
	FGameItemInfo iteminfo;
	iteminfo.m_ItemRecKey = ItemReckey;
	for (int index = 0; index < m_ItemArray.Num(); ++index)
	{
		if (m_ItemArray[index].m_ItemRecKey == iteminfo.m_ItemRecKey)
		{
			iteminfo.m_ItemCount += m_ItemArray[index].m_ItemCount;
		}
	}
	return iteminfo;
}

int32 UItemMgr::CountItemEqupiment(int32 ItemReckey)
{
	int32 count = 0;

	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index].m_ItemRecKey == ItemReckey)
		{
			++count;
		}
	}

	return count;
}

FGameItemEquipmentInfo UItemMgr::FindItemEquipmentWorstStat(int32 ItemReckey)
{
	FGameItemEquipmentInfo iteminfo;
	for (int index = 0; index < m_ItemEquipmentArray.Num(); ++index)
	{
		if (m_ItemEquipmentArray[index].m_ItemRecKey == ItemReckey)
		{
			if (iteminfo.m_ItemRecKey == 0 || iteminfo.m_ItemUgrapeLevel > m_ItemEquipmentArray[index].m_ItemUgrapeLevel)
			{
				iteminfo = m_ItemEquipmentArray[index];
			}
		}
	}
	return iteminfo;
}
