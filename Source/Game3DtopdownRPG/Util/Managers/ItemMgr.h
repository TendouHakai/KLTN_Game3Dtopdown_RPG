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

	FString GetItemGradeText(EItemGrade grade);
	FString GetDescriptionItem(const FItemInfoRecord& ItemInfoRecord);

	// item equipment
	FItemEquipmentInfoRecord* GetItemEquipmentInfoRecord(FName Index);
protected:
	TArray<FGameItemInfo> m_ItemArray;
};
