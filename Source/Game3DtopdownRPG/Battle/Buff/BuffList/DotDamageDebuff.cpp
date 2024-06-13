// Fill out your copyright notice in the Description page of Project Settings.


#include "DotDamageDebuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

UDotDamageDebuff::UDotDamageDebuff()
{

}

void UDotDamageDebuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	DotPeriod = CheckBuffInfo.Duration;
	RemainDotPeriod = DotPeriod;

	float _DotAmount = 0.0f;
	if (0 < CheckBuffInfo.BuffAmount.Num())
		_DotAmount = CheckBuffInfo.BuffAmount[0];

	Duration = 1;
	bIsPassiveBuff = false;

	ConvertToPercent(_DotAmount);
	DotAmount =_DotAmount;
}

void UDotDamageDebuff::TimeEndFunction()
{
	ElapseTime = 0.0f;
	DamageOverTime();
}

void UDotDamageDebuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	PeriodElapseTime = 0.0f;
	RemainDotPeriod = DotPeriod;
	UpdateDebuffResist();
}

void UDotDamageDebuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PeriodElapseTime += DeltaTime;
}

void UDotDamageDebuff::UpdateDebuffResist()
{
	RemainDotPeriod = RemainDotPeriod * (1.0f - OwnerCharacter->GetDeBuffResistRatio());
}

const int32 UDotDamageDebuff::GetRemainTime()
{
	return RemainDotPeriod;
}

void UDotDamageDebuff::DamageOverTime()
{
	RemainDotPeriod += -1;

	Damage();

	UpdateBuffInfo();

	if (0 >= RemainDotPeriod)
		EndBuff();
}

void UDotDamageDebuff::Damage()
{
	if (0.0f >= OwnerCharacter->getHP()
		|| OwnerCharacter->GetAnimState() == EChrAnimState::Die)
		return;

	float DotDamage = OwnerCharacter->getMaxHP() * DotAmount;
	//GuildRaidException(DotDamage);

	OwnerCharacter->ReceiveDamage(CasterCharacter, DotDamage, bMagicDamage, HeroBuffInfo.bForcedBuff);
}

void UDotDamageDebuff::GuildRaidException(float& DotDamage)
{

}
