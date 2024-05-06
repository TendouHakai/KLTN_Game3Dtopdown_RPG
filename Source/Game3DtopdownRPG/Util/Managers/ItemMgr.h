// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "ItemMgr.generated.h"

struct FItemInfoRecord;
struct FGameItemInfo;

UCLASS()
class GAME3DTOPDOWNRPG_API UItemMgr : public USingleton
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void EndPlay() override;

	FItemInfoRecord* GetItemInfoRecord(FName Index);
	TArray<FGameItemInfo> GetItemArray();

protected:
	TArray<FGameItemInfo> m_ItemArray;
};
