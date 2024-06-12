// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleStruct.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	PhysDamOnly,
	MagDamOnly,
	All,
};

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

USTRUCT(BlueprintType)
struct FNativeSkillInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CoolDownDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CoolDownTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EBattleSkillState state;

	GENERATED_USTRUCT_BODY()

	FNativeSkillInfo()
		: CoolDownDuration(0.0f)
		, CoolDownTime(0.0f)
		, state(EBattleSkillState::Available)
	{}
};