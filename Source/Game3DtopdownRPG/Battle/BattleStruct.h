// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleStruct.generated.h"

UENUM(BlueprintType)
enum class EBattleClearStep : uint8
{
	None,
	GetItem,
	ReadyVictory,
	Failed,
	Victory,
};
