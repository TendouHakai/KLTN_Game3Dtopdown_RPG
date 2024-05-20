// Fill out your copyright notice in the Description page of Project Settings.


#include "CppFunctionLibrary.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"

UTableMgr* UCppFunctionLibrary::GetTableMgr()
{
	return GetMgr(UTableMgr);
}

UAssetMgr* UCppFunctionLibrary::GetAssetMgr()
{
	return GetMgr(UAssetMgr);
}

UItemMgr* UCppFunctionLibrary::GetItemMgr()
{
	return GetMgr(UItemMgr);
}

UHeroMgr* UCppFunctionLibrary::GetHeroMgr()
{
	return GetMgr(UHeroMgr);
}

UObject* UCppFunctionLibrary::GetDefaultObject(TSubclassOf<UObject> ObjectClass)
{
	if (!ObjectClass)
		return nullptr;
	else
		return ObjectClass->GetDefaultObject();
}

FCharacterParam UCppFunctionLibrary::GetHeroParamLevel(const FCharacterParam& HeropramBase, const FCharacterParam& HeroparamUpgrade, int32 Lev)
{
	FCharacterParam param;
	param.PhysicDamage = HeropramBase.PhysicDamage + HeroparamUpgrade.PhysicDamage * Lev;
	param.MagicDamage = HeropramBase.MagicDamage + HeroparamUpgrade.MagicDamage * Lev;
	param.HP = HeropramBase.HP + HeroparamUpgrade.HP * Lev;
	param.Def = HeropramBase.Def + HeroparamUpgrade.Def * Lev;
	param.MagicDef = HeropramBase.MagicDef + HeroparamUpgrade.MagicDef * Lev;
	param.AttackSpeedRate = HeropramBase.AttackSpeedRate + HeroparamUpgrade.AttackSpeedRate * Lev;
	param.MovementSpeedRate = HeropramBase.MovementSpeedRate + HeroparamUpgrade.MovementSpeedRate * Lev;
	param.ReduceCoolDownRatio = HeropramBase.ReduceCoolDownRatio + HeroparamUpgrade.ReduceCoolDownRatio * Lev;
	param.CriticalRatio = HeropramBase.CriticalRatio + HeroparamUpgrade.CriticalRatio * Lev;
	param.HealHP = HeropramBase.HealHP + HeroparamUpgrade.HealHP * Lev;
	param.PierceDef = HeropramBase.PierceDef + HeroparamUpgrade.PierceDef * Lev;
	param.PierceMagicDef = HeropramBase.PierceMagicDef + HeroparamUpgrade.PierceMagicDef * Lev;
	param.DebuffResistanceRatio = HeropramBase.DebuffResistanceRatio + HeroparamUpgrade.DebuffResistanceRatio * Lev;
	return param;
	//return FCharacterParam();
}
