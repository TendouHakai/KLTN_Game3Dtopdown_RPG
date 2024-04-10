// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// GetMgr
UObject* GetMgrFunc(UClass* MgrClass);
#define GetMgr(MgrClass) Cast<MgrClass>(GetMgrFunc(MgrClass::StaticClass()))

// GetGameModeAs
class AGameMode* GetGameModeAsFunc();

template<class GameModeClass>
GameModeClass* GetGameModeAsTFunc() { return Cast<GameModeClass>(GetGameModeAsFunc()); }

#define GetGameModeAs(GameModeClass) GetGameModeAsTFunc<GameModeClass>()
