// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageDebuff.h"
#include "AttackDamageDebuff.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAME3DTOPDOWNRPG_API UAttackDamageDebuff : public UDamageDebuff
{
	GENERATED_BODY()
public:
	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual float CalculateDamPercent(bool bMagicDamage, ABaseCharacter* Attacker) override;

private:
	int32 TargetDamage{ 0 };
};
