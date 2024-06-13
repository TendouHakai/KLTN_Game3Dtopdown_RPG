// Fill out your copyright notice in the Description page of Project Settings.


#include "PeriodHealBuff.h"

UPeriodHealBuff::UPeriodHealBuff()
{
}

void UPeriodHealBuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	HealPeriod = CheckBuffInfo.Duration;
	RemainHealPeriod = HealPeriod;

	HealAmount = HealAmount / HealPeriod;

	Duration = 1.0f;
}

void UPeriodHealBuff::BeginBuff()
{
	Super::BeginBuff();

	RemainHealPeriod += -1;
}

void UPeriodHealBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PeriodElapseTime += DeltaTime;
}

void UPeriodHealBuff::PeriodHeal()
{
	if (0 >= RemainHealPeriod)
		EndBuff();
	else
	{
		RemainHealPeriod +=-1;
		Heal();
	}
}

void UPeriodHealBuff::TimeEndFunction()
{
	ElapseTime = 0.0f;
	PeriodHeal();
}

void UPeriodHealBuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	RemainHealPeriod = HealPeriod;
	PeriodElapseTime = 0;
}
