// Fill out your copyright notice in the Description page of Project Settings.


#include "CppFunctionLibrary.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffControllerComponent.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

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

FText UCppFunctionLibrary::ToMinutsText_NoGap(int32 InSeconds)
{
	if (InSeconds < 0)
		InSeconds = 0;

	static FText temp;

	FTimespan TimeSpan(ETimespan::TicksPerSecond * (int64)InSeconds);


	int32 Hours = TimeSpan.GetTotalHours();
	int32 Minnutes = TimeSpan.GetMinutes();
	int32 Seconds = TimeSpan.GetSeconds();

	FString strHour, strMin, strSec, strTemp;

	strTemp = TEXT(":");

	if (Hours > 0)
	{
		if (Hours < 10)
			strHour = FString::Printf(TEXT("0%d"), Hours);
		else
			strHour = FString::FormatAsNumber(Hours);

		strHour += strTemp;
	}


	if (Minnutes < 10)
		strMin = FString::Printf(TEXT("0%d"), Minnutes);
	else
		strMin = FString::FormatAsNumber(Minnutes);

	strMin += strTemp;

	strHour += strMin;

	if (Seconds < 10)
		strSec = FString::Printf(TEXT("0%d"), Seconds);
	else
		strSec = FString::FormatAsNumber(Seconds);

	strHour += strSec;

	temp = FText::FromString(strHour);
	return temp;
}

void UCppFunctionLibrary::FindHaveBuff(AActor* Target, const UClass* ClassType, TArray<UBaseBuff*>& BuffArray)
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Target);

	if (nullptr == BaseCharacter)
		return;

	BaseCharacter->FindHaveBuff(ClassType, BuffArray);
}
