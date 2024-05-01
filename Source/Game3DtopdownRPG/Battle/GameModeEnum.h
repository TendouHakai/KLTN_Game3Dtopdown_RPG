// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	None,
	Login,
	Lobby,
	Battle
};

UENUM(BlueprintType)
enum class EBattleGameModeState : uint8
{
	None,
	BattleStart,
	PlayingBattle,
	Max,
};