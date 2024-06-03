// Fill out your copyright notice in the Description page of Project Settings.


#include "TableMgr.h"
#include "AssetMgr.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"
#include "UObject/ConstructorHelpers.h"

#include "Game3DtopdownRPG/DataTable/ItemTable.h"

void UTableMgr::Init()
{
	Super::Init();

	HeroInfoTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Hero/HeroTable.HeroTable"));
	HeroLevTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Hero/HeroLevTable.HeroLevTable"));
	HeroLevParamTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Hero/HeroParamLevTable.HeroParamLevTable"));
	BuffInfoTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Buff/BuffInfoTable.BuffInfoTable"));

	ItemInfoTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Item/ItemInfoTable.ItemInfoTable"));
	ItemTypeInfoTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Item/ItemTypeInfoTable.ItemTypeInfoTable"));
	ItemEquipmentInfoTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Item/ItemEquipment/ItemEquipmentInfoTable.ItemEquipmentInfoTable"));
	ItemEquipmentLevInfoTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Item/ItemEquipment/ItemEquipmentLevInfoTable.ItemEquipmentLevInfoTable"));
	UpgradeLevelOfMaterialTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Item/UpgardeItemMaterial/UpgradeLevelOfMaterialTable.UpgradeLevelOfMaterialTable"));
	ItemParamLevTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Item/ItemEquipment/ItemParamLevTable.ItemParamLevTable"));
	ExpForItemGradeTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Item/ItemEquipment/ExpForItemGradeTable.ExpForItemGradeTable"));
}

void UTableMgr::EndPlay()
{
	Super::EndPlay();
}

void UTableMgr::Tick()
{
}

void UTableMgr::Destroy()
{
	Super::Destroy();
}
