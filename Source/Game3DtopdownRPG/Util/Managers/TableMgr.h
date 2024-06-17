// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "Engine/DataTable.h"

#include "TableMgr.generated.h"

struct FItemInfoRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UTableMgr : public USingleton
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	//void Init(class ABaseGameMode* CurGameMode);

	virtual void EndPlay() override;
	virtual void Tick();

	virtual void Destroy() override;

public:
	// Hero
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* HeroInfoTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* HeroLevTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* HeroLevParamTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* SkillInfoTable;

	// Buff
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* BuffInfoTable;

	// Item
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ItemInfoTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ItemTypeInfoTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ItemEquipmentInfoTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ItemEquipmentLevInfoTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* UpgradeLevelOfMaterialTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ItemParamLevTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ExpForItemGradeTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ItemBuffTable;

	// Map
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* StageInfoTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TableMgr") UDataTable* ChapterInfoTable;
};
