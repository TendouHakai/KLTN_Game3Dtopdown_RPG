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

USTRUCT(BlueprintType)
struct FGameItemInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemRecKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	bool m_IsInBackpack;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)	int64 m_RemainTime;

	GENERATED_USTRUCT_BODY()
public:
	FGameItemInfo(int32 ItemCount = 0, int32 ItemRecKey = 0, bool IsInBackpack = false)
	{
		m_ItemCount = ItemCount;
		m_ItemRecKey = ItemRecKey;
		m_IsInBackpack = IsInBackpack;
	}
};

USTRUCT(BlueprintType)
struct FGameItemEquipmentInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemRecKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_ItemUgrapeLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	bool m_IsInBackpack;

	GENERATED_USTRUCT_BODY()
public:
	FGameItemEquipmentInfo(int32 ItemRecKey = 0, int32 ItemUgrapeLevel = 0, bool IsInBackpack = false)
	{
		m_ItemRecKey = ItemRecKey;
		m_ItemUgrapeLevel = ItemUgrapeLevel;
		m_IsInBackpack = IsInBackpack;
	}

	bool operator==(const FGameItemEquipmentInfo& Other) const
	{
		return (this->m_ItemRecKey == Other.m_ItemRecKey) && (this->m_ItemUgrapeLevel == Other.m_ItemUgrapeLevel) && (this->m_IsInBackpack == m_IsInBackpack);
	}
};
