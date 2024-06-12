// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "SavedInventoryConfig.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API USavedInventoryConfig : public USaveGame
{
	GENERATED_BODY()
public:
	USavedInventoryConfig();

	UFUNCTION(BlueprintCallable, Category = "SavedUserConfig")
	static void SaveInventoryCfgToFile(USavedInventoryConfig* Cfg);

	UFUNCTION(BlueprintCallable, Category = "SavedUserConfig")
	static USavedInventoryConfig* LoadInventoryCfgFromFile(bool& bSuccess);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameItemInfo> m_ItemArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameItemEquipmentInfo> m_ItemEquipmentArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Gold;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnergyResetTime;
};
