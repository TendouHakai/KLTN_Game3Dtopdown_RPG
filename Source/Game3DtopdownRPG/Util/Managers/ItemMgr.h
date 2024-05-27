// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "ItemMgr.generated.h"

struct FItemInfoRecord;
struct FItemEquipmentInfoRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UItemMgr : public USingleton
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void EndPlay() override;

	// Item info
	FItemInfoRecord* GetItemInfoRecord(FName Index);
	TArray<FGameItemInfo> GetItemArray();
	TArray<FGameItemInfo> GetItemInInventoryArray();
	TArray<FGameItemInfo> GetItemInBackpackArray();

	FString GetItemGradeText(EItemGrade grade);
	FString GetDescriptionItem(const FItemInfoRecord& ItemInfoRecord);

	// item equipment
	TArray<FGameItemEquipmentInfo> GetItemEquipmentArray() { return m_ItemEquipmentArray; }
	TArray<FGameItemEquipmentInfo> GetItemEquipmentInInventoryArray();
	TArray<FGameItemEquipmentInfo> GetItemEquipmentInBackpackArray();
	FItemEquipmentInfoRecord* GetItemEquipmentInfoRecord(FName Index);
	UFUNCTION(BlueprintCallable)
	FItemEquipmentInfoRecord GetItemEquipmentInfoRecordBlueprint(FName Index);

	// Cheat Item
	void AddItem(int32 ItemReckey = 1, int32 ItemCount = 1, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory);
	void AddItemEquipment(int32 ItemEquipmentReckey = 1, int32 ItemUpgradeLevel = 1, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory);

	void ChangeItemInventoryLocation(FGameItemInfo iteminfo, int ItemCount, EInventoryLocation Inventorylocation);
	void ChangeItemEquipmentInventoryLocation(FGameItemEquipmentInfo iteminfo, EInventoryLocation Inventorylocation);
protected:
	TArray<FGameItemInfo> m_ItemArray;
	TArray<FGameItemEquipmentInfo> m_ItemEquipmentArray;
};
