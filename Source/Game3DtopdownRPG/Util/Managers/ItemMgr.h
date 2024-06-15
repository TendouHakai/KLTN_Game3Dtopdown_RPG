// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "ItemMgr.generated.h"

struct FItemInfoRecord;
struct FItemEquipmentInfoRecord;
struct FItemTypeInfoRecord;
struct FItemEquipmentLevRecord;
struct FUpgradeLevelOfMaterialRecord;
struct FItemParamLevRecord;
struct FExpForGradeRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UItemMgr : public USingleton
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void EndPlay() override;

	// record
	FItemInfoRecord* GetItemInfoRecord(FName Index);
	FItemEquipmentInfoRecord* GetItemEquipmentInfoRecord(FName Index);
	FItemEquipmentLevRecord* GetItemEquipmentLevelRecord(FName Index);
	FUpgradeLevelOfMaterialRecord* GetUpgradeLevelOfMaterialRecord(FName Index);
	FItemParamLevRecord* GetItemParamLevRecord(FName Index);
	FExpForGradeRecord* GetExpForGradeRecord(FName Index);
	FItemTypeInfoRecord* GetItemTypeInfoRecord(FName Index);
	
	TArray<FGameItemInfo> GetAllItemRecipeByItemType(EItemType type);

	// Upgrade Item
	FItemEquipmentLevRecord* GetItemEquipmentLevelRecordByTotalExp(int32 totalExp);
	int32 GetMaxEquipmentLevelByTotalExp();

	// item normal
	TArray<FGameItemInfo> GetItemArray();
	TArray<FGameItemInfo> GetItemInInventoryArray();
	TArray<FGameItemInfo> GetItemInBackpackArray();
	TArray<FGameItemInfo> GetItemArrayByItemType(EItemType type, EInventoryLocation location = EInventoryLocation::InInventory);
	TArray<FGameItemInfo> GetItemArrayByCategory(EItemCategory category, EInventoryLocation location = EInventoryLocation::InInventory);

	FString GetItemGradeText(EItemGrade grade);
	FString GetDescriptionItem(const FItemInfoRecord& ItemInfoRecord);

	// item equipment
	TArray<FGameItemEquipmentInfo> GetItemEquipmentArray() { return m_ItemEquipmentArray; }
	TArray<FGameItemEquipmentInfo> GetItemEquipmentInInventoryArray();
	TArray<FGameItemEquipmentInfo> GetItemEquipmentInBackpackArray();
	TArray<FGameItemEquipmentInfo> GetItemEquipmentArrayByEquipPosition(EItemEquipPosition position, EInventoryLocation location);

	UFUNCTION(BlueprintCallable)
	FItemEquipmentInfoRecord GetItemEquipmentInfoRecordBlueprint(FName Index);

	// item forging
	TArray<FGameItemEquipmentInfo> GetAllItemEquipmentRecipe();
	EResult ForgingItemEquipment(int32 ItemReckey, int32 count, int32 &errorcode);

	// Item making
	EResult MakeItem(int32 ItemReckey, int32 count, int32& errorcode);

	// Cheat Item
	UFUNCTION(BlueprintCallable)
	void AddItem(int32 ItemReckey = 1, int32 ItemCount = 1, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory);
	void RemoveItem(int32 ItemReckey = 1, int32 ItemCount = 1, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory);
	UFUNCTION(BlueprintCallable)
	void AddItemEquipment(int32 ItemEquipmentReckey = 1, int32 ItemUpgradeLevel = 1, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory);
	void RemoveItemEquipment(FGameItemEquipmentInfo iteminfo);

	void ChangeItemInventoryLocation(FGameItemInfo iteminfo, int ItemCount, EInventoryLocation Inventorylocation);
	void ChangeItemEquipmentInventoryLocation(FGameItemEquipmentInfo iteminfo, EInventoryLocation Inventorylocation);

	FGameItemEquipmentInfo UpgradeLevelItemEquipment(FGameItemEquipmentInfo iteminfo, TArray<FGameItemInfo> Materials);
	bool isHaveEquipmentItem(FGameItemEquipmentInfo iteminfo);

	FGameItemInfo FindItem(int32 ItemReckey);
	int32 CountItemEqupiment(int32 ItemReckey);
	FGameItemEquipmentInfo FindItemEquipmentWorstStat(int32 ItemReckey);

	// Gold
	int64 GetGold() { return Gold; }
	UFUNCTION(BlueprintCallable)
	void AddGold(int64 gold) { Gold = Gold + gold; }

	// Energy
	int64 GetEnergy() { return Energy; }
	int64 GetMaxEnergy() { return MaxEnergy; }
	void AddEnergy(int64 energy, bool isResetTime = false) 
	{ 
		if(isResetTime || Energy >= MaxEnergy)
			EnergyResetTime = FDateTime::Now().GetTimeOfDay().GetTotalSeconds();

		Energy = Energy + energy;
		if (Energy > MaxEnergy) Energy = MaxEnergy;
	}
	float GetEnergyResetTime() { return EnergyResetTime; }
	float GetEnergyRemainTime() { return EnergyRemainTime; }
protected:
	TArray<FGameItemInfo> m_ItemArray;
	TArray<FGameItemEquipmentInfo> m_ItemEquipmentArray;
	int Gold;

	int Energy;
	int MaxEnergy = 30;
	float EnergyResetTime;
	float EnergyRemainTime = 30;
};
