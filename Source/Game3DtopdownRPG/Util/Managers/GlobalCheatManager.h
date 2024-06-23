// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffStruct.h"
#include "GlobalCheatManager.generated.h"

UCLASS()
class GAME3DTOPDOWNRPG_API UGlobalCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void ItemAdd(int32 ItemReckey = 1, int32 ItemCount = 1, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory);

	UFUNCTION(Exec)
	void ItemEquipmentAdd(int32 ItemEquipmentReckey = 1, int32 ItemUpgradeLevel = 1, EInventoryLocation InventoryLocation = EInventoryLocation::InInventory);

	UFUNCTION(Exec)
	void Gold(int64 gold = 0);

	UFUNCTION(Exec)
	void Energy(int64 energy = 0);

	UFUNCTION(Exec)
	void MapClear(int32 StageReckey = 1);

	UFUNCTION(Exec)
	void AddBuff(EHeroBuffType bufftype = EHeroBuffType::None_Buff, int32 buffCondition = 0 , EBuffTargetType target = EBuffTargetType::Self, float duration = 1.0f, float bufffamount1 = 0.f, float buffamount2 = 0.f, float buffamount3 = 0.f);

	void Endcheat();
};
