// Fill out your copyright notice in the Description page of Project Settings.


#include "HealBuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

UHealBuff::UHealBuff()
{
}

void UHealBuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);

	HealTarget = CheckBuffInfo.BuffTarget;
	float _HealAmout = 0.f;

	if (0 < CheckBuffInfo.BuffAmount.Num())
		_HealAmout = CheckBuffInfo.BuffAmount[0];
	ConvertToPercent(_HealAmout);
	HealAmount = _HealAmout;
	Duration = 2.0f;
	bIsPassiveBuff = false;
}

void UHealBuff::BeginBuff()
{
	Super::BeginBuff();

	Heal();
}

bool UHealBuff::IsSelfHeal()
{
	if (EBuffTargetType::Self == HealTarget)
		return true;

	return false;
}

void UHealBuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	Super::RenewBuff(RenewBuffInfo);

	Heal();
}

float UHealBuff::GetHealPercent()
{
	return HealAmount;
}

void UHealBuff::Heal()
{
	if (0.0f >= OwnerCharacter->getHP())
		return;

	//if (true == OwnerCharacter->IsHaveBuff(UHealBan::StaticClass()))
	//	return;

	float HealPercent = GetHealPercent();

	HealingRecoveryIncrease(HealPercent);
	HealingRecoveryDecrease(HealPercent);
	GuildRaidExcept(HealPercent);
	BleedingDebuffHealSubtraction(HealPercent);

	OwnerCharacter->CharacterHeal(HealPercent);
}

void UHealBuff::GuildRaidExcept(float& HealPercent)
{
}

void UHealBuff::BleedingDebuffHealSubtraction(float& HealPercent)
{
}

void UHealBuff::HealingRecoveryDecrease(float& HealPercent)
{
}

void UHealBuff::HealingRecoveryIncrease(float& HealPercent)
{
}
