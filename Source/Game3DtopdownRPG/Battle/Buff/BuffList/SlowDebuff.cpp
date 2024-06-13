// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowDebuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

void USlowDebuff::BeginBuff()
{
	Super::BeginBuff();

	OwnerCharacter->UpdateMoveSpeedRate();
	OwnerCharacter->UpdateAttackSpeedRate();
}

void USlowDebuff::EndBuff(bool bForcedEnd /* = false */)
{
	Super::EndBuff(bForcedEnd);

	OwnerCharacter->UpdateMoveSpeedRate();
	OwnerCharacter->UpdateAttackSpeedRate();
}

void USlowDebuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	float _SpeedPercent = 0.0f;
	if (0 < CheckBuffInfo.BuffAmount.Num())
		_SpeedPercent = CheckBuffInfo.BuffAmount[0];

	ConvertToPercent(_SpeedPercent);

	SpeedPercent = _SpeedPercent;
}

float USlowDebuff::GetUpdateSpeed()
{
	return SpeedPercent;
}
