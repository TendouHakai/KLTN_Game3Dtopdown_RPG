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


UENUM(BlueprintType)
enum class EBattleSkillState : uint8
{
	Available,
	Using,
	Cooldown,
	Max,
};

UENUM(BlueprintType)
enum class EBattleSkillProcResult : uint8
{
	Success,
	Failed,
	Max,
};