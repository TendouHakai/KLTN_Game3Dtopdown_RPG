// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Managers/AssetMgr.h"
#include "Managers/TableMgr.h"

#include "UObject/NoExportTypes.h"
#include "CppFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UCppFunctionLibrary : public UObject
{
	GENERATED_BODY()

public:
	// Get Mgr
	UFUNCTION(BlueprintPure, Category = "Table Singleton")
	static UTableMgr* GetTableMgr();

	UFUNCTION(BlueprintPure, Category = "AssetMgr Singleton")
	static UAssetMgr* GetAssetMgr();

	UFUNCTION(BlueprintCallable, Category = "CppFunctionLibrary")
	static UObject* GetDefaultObject(TSubclassOf<UObject> ObjectClass);
};
