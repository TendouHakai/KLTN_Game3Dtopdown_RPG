// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackDamageBuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/BattleStruct.h"

void UAttackDamageBuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	if (CheckBuffInfo.BuffAmount.IsValidIndex(1))
	{
		BuffTargetDamage = CheckBuffInfo.BuffAmount[1];
	}
}

float UAttackDamageBuff::CalculateDamPercent(bool bMagicDamage, ABaseCharacter* Attacker)
{
	if ((true == bMagicDamage && (int32)EDamageType::PhysDamOnly == DamageBuffType)
		|| (false == bMagicDamage && (int32)EDamageType::MagDamOnly == DamageBuffType))
		return 0.0f;
		
	if (IsValid(Attacker) == false)
	{
		return 0.0f;
	}

	//if (CheckValidDamageType(BuffTargetDamage, Attacker->GetAnimState()) == false)
	//{
	//	return 0.0f;
	//}

	return InfluenceAmount;
}

int32 UAttackDamageBuff::BuffStateIndex()
{
	switch (DamageBuffType)
	{
	case (int32)EDamageType::PhysDamOnly: return (int32)EBuffEffectType::Inc_PhysicsDamage;
	case (int32)EDamageType::MagDamOnly: return (int32)EBuffEffectType::Inc_MagicDamage;
	case (int32)EDamageType::All: return (int32)EBuffEffectType::Inc_AllDamage;
	}

	return -1;
}
