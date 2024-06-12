// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackDamageDebuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/BattleStruct.h"

void UAttackDamageDebuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	if (CheckBuffInfo.BuffAmount.IsValidIndex(1))
	{
		TargetDamage = CheckBuffInfo.BuffAmount[1];
	}
}

float UAttackDamageDebuff::CalculateDamPercent(bool bMagicDamage, ABaseCharacter* Attacker)
{
	if ((true == bMagicDamage && (int32)EDamageType::PhysDamOnly == DamageBuffType)
		|| (false == bMagicDamage && (int32)EDamageType::MagDamOnly == DamageBuffType))
		return 0.0f;

	if (IsValid(Attacker) == false)
	{
		return 0.0f;
	}

	//if (CheckValidDamageType(TargetDamage, Attacker->GetAnimState()) == false)
	//{
	//	return 0.0f;
	//}

	return InfluenceAmount * -1.0f;
}
