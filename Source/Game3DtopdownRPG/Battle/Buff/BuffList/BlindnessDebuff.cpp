// Fill out your copyright notice in the Description page of Project Settings.


#include "BlindnessDebuff.h"

void UBlindnessDebuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	if (0 < CheckBuffInfo.BuffAmount.Num())
		BlindnessPercent = CheckBuffInfo.BuffAmount[0];
}
