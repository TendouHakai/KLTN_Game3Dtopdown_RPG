// Fill out your copyright notice in the Description page of Project Settings.


#include "BleedingDeBuff.h"

void UBleedingDeBuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	bMagicDamage = false;
}
