 // Fill out your copyright notice in the Description page of Project Settings.


#include "DamageDebuff.h"

UDamageDebuff::UDamageDebuff()
{
}

void UDamageDebuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	DamageBuffType = CheckBuffInfo.BuffCondition;

	InitInfluenceAmount(CheckBuffInfo);
}

void UDamageDebuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	Super::RenewBuff(RenewBuffInfo);

	InitInfluenceAmount(RenewBuffInfo);
	SetBuffInfoText();
}

void UDamageDebuff::CopyBuff(const UBaseBuff* OriginBuff)
{
	Super::CopyBuff(OriginBuff);

	InitInfluenceAmount(HeroBuffInfo);
	SetBuffInfoText();
}

void UDamageDebuff::InitInfluenceAmount(const FHeroBuffInfo& BuffInfo)
{
	float _BuffAmount = 0.0f;
	if (0 < BuffInfo.BuffAmount.Num())
		_BuffAmount = BuffInfo.BuffAmount[0];

	_BuffAmount *= CurrentStack;
	ConvertToPercent(_BuffAmount);

	InfluenceAmount = _BuffAmount;
}
