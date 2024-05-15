// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Managers/AssetMgr.h"
#include "Managers/TableMgr.h"
#include "Managers/ItemMgr.h"

#include "UObject/NoExportTypes.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
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

	UFUNCTION(BlueprintPure, Category = "ItemMgr Singleton")
	static UItemMgr* GetItemMgr();

	UFUNCTION(BlueprintCallable, Category = "CppFunctionLibrary")
	static UObject* GetDefaultObject(TSubclassOf<UObject> ObjectClass);

	// Character Param
	UFUNCTION(BlueprintCallable, Category = "CppFunctionLibrary")
	static FCharacterParam GetHeroParamLevel(const FCharacterParam& HeropramBase, const FCharacterParam& HeroparamUpgrade, int32 Lev);
};
