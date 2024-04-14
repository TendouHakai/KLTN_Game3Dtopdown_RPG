// Fill out your copyright notice in the Description page of Project Settings.


#include "TableMgr.h"
#include "AssetMgr.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"
#include "UObject/ConstructorHelpers.h"

void UTableMgr::Init()
{
	Super::Init();

	HeroInfoTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Hero/HeroTable.HeroTable"));
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
