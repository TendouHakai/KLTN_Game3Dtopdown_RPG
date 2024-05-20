// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "GlobalCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UGlobalCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void ItemAdd(int32 ItemReckey = 1, int32 ItemCount = 1, bool IsInBakcpack = false);

	UFUNCTION(Exec)
	void ItemEquipmentAdd(int32 ItemEquipmentReckey = 1, int32 ItemUpgradeLevel = 1, bool IsInBakcpack = false);

	void Endcheat();
};
