// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageBuff.h"

UDamageBuff::UDamageBuff()
{

}

void UDamageBuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	DamageBuffType = CheckBuffInfo.BuffCondition;

	InitInfluenceAmount(CheckBuffInfo);
}

void UDamageBuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	Super::RenewBuff(RenewBuffInfo);

	InitInfluenceAmount(RenewBuffInfo);
	SetBuffInfoText();
}

void UDamageBuff::CopyBuff(const UBaseBuff* OriginBuff)
{
	Super::CopyBuff(OriginBuff);

	InitInfluenceAmount(HeroBuffInfo);
	SetBuffInfoText();
}

void UDamageBuff::InitInfluenceAmount(const FHeroBuffInfo& BuffInfo)
{
	float _BuffAmount = 0.0f;
	if (0 < BuffInfo.BuffAmount.Num())
		_BuffAmount = BuffInfo.BuffAmount[0];

	_BuffAmount *= CurrentStack;
	ConvertToPercent(_BuffAmount);

	InfluenceAmount =_BuffAmount;
}
