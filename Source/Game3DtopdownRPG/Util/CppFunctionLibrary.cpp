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

UObject* UCppFunctionLibrary::GetDefaultObject(TSubclassOf<UObject> ObjectClass)
{
	if (!ObjectClass)
		return nullptr;
	else
		return ObjectClass->GetDefaultObject();
}
