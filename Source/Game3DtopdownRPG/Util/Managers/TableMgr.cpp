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
