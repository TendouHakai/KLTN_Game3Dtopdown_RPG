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
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)	int64 m_RemainTime;

	GENERATED_USTRUCT_BODY()
public:
	FGameItemInfo(int32 ItemCount = 0, int32 ItemRecKey = 0, uint8 ItemGrade = 0/*, int64 RemainTime = 0*/)
	{
		m_ItemCount = ItemCount;
		m_ItemRecKey = ItemRecKey;
	}
};
