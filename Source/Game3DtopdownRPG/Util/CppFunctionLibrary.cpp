// Fill out your copyright notice in the Description page of Project Settings.


#include "CppFunctionLibrary.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"

UTableMgr* UCppFunctionLibrary::GetTableMgr()
{
	return GetMgr(UTableMgr);
}

UAssetMgr* UCppFunctionLibrary::GetAssetMgr()
{
	return GetMgr(UAssetMgr);
}
