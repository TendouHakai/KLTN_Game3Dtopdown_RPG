// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageBuff.h"
#include "AttackDamageBuff.generated.h"

UCLASS(Blueprintable)
class GAME3DTOPDOWNRPG_API UAttackDamageBuff : public UDamageBuff
{
	GENERATED_BODY()
public:
	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;

	virtual float CalculateDamPercent(bool bMagicDamage, ABaseCharacter* Attacker) override;

	virtual int32 BuffStateIndex() override;

public:
	enum
	{
		eBuffDamageAll = 0,
		eBuffDamagePhysics,
		eBuffDamageSkill,
	};

	int32 BuffTargetDamage{ 0 };
};
