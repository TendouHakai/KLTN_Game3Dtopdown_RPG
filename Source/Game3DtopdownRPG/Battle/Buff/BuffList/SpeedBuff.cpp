// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBuff.h"

void USpeedBuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	float _SpeedPercent = 0.0f;
	if (0 < CheckBuffInfo.BuffAmount.Num())
		_SpeedPercent = CheckBuffInfo.BuffAmount[0];

	ConvertToPercent(_SpeedPercent);

	SpeedPercent = _SpeedPercent;
}

float USpeedBuff::GetUpdateSpeed()
{
	return SpeedPercent;
}
