// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	All,			
	Common,		
	Material,
	Potion,
	Max
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	UpgradeEquipmentItem,
	Max
};

UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	Normal,		
	High,		
	Rare,		
	Hero,		
	Legend,	
	Max
};

UENUM(BlueprintType)
enum class EInventoryLocation : uint8
{
	InInventory,
	InBackpack,
	InEquipment,
	Max
};

USTRUCT(BlueprintType)
struct FGameItemInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemRecKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	EInventoryLocation m_InventoryLocation;

	GENERATED_USTRUCT_BODY()
public:
	FGameItemInfo(int32 ItemCount = 0, int32 ItemRecKey = 0, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory)
	{
		m_ItemCount = ItemCount;
		m_ItemRecKey = ItemRecKey;
		m_InventoryLocation = InventoryLocation;
	}
};

USTRUCT(BlueprintType)
struct FGameItemEquipmentInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemRecKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemUgrapeLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	EInventoryLocation m_InventoryLocation;

	GENERATED_USTRUCT_BODY()
public:
	FGameItemEquipmentInfo(int32 ItemRecKey = 0, int32 ItemUgrapeLevel = 0, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory)
	{
		m_ItemRecKey = ItemRecKey;
		m_ItemUgrapeLevel = ItemUgrapeLevel;
		m_InventoryLocation = InventoryLocation;
	}

	bool operator==(const FGameItemEquipmentInfo& Other) const
	{
		return (this->m_ItemRecKey == Other.m_ItemRecKey) && (this->m_ItemUgrapeLevel == Other.m_ItemUgrapeLevel) && (this->m_InventoryLocation == Other.m_InventoryLocation);
	}
};
