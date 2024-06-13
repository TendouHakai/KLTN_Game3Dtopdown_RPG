// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDebuff.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

void UBaseDebuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	Super::InitBuff(Caster, CheckBuffInfo);
	UpdateDebuffResist();

	if (nullptr == Caster)
		return;

	CastBuffAnimState = Caster->GetAnimState();
}

void UBaseDebuff::BeginBuff()
{
	Super::BeginBuff();
	if (CheckCrowdControl())
		UpdateFakeCCBuff();
}

bool UBaseDebuff::IsSameBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	if (Caster != CasterCharacter)
		return false;

	if (HeroBuffInfo.BuffType != CheckBuffInfo.BuffType)
		return false;

	if (HeroBuffInfo.BuffCondition != CheckBuffInfo.BuffCondition)
		return false;

	if (HeroBuffInfo.BuffAmount.Num() != CheckBuffInfo.BuffAmount.Num())
		return false;

	for (int i = 0; i < HeroBuffInfo.BuffAmount.Num(); ++i)
	{
		if (HeroBuffInfo.BuffAmount[i] != CheckBuffInfo.BuffAmount[i])
			return false;
	}

	if (Caster->GetAnimState() != CastBuffAnimState)
		return false;

	return true;
}

void UBaseDebuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	float RemainTime = Duration - ElapseTime;

	if (RemainTime <= RenewBuffInfo.Duration)
	{
		Duration = RenewBuffInfo.Duration;
		UpdateDebuffResist();
	}

	ElapseTime = 0.0f;
}

void UBaseDebuff::UpdateFakeCCBuff()
{
	TArray<UBaseBuff*> FakeCCBuffs;
	//OwnerCharacter->FindHaveBuff(UCFakeCrowdControlBuff::StaticClass(), FakeCCBuffs);

	//for (UCBaseBuff* FakeCCBuff : FakeCCBuffs)
	//{
	//	UCFakeCrowdControlBuff* FakeCrowdControlBuff = Cast<UCFakeCrowdControlBuff>(FakeCCBuff);
	//	FakeCrowdControlBuff->OnFakeCrowdControl(true);
	//}
}

void UBaseDebuff::UpdateDebuffResist()
{
	float DeBuffResistRatio = OwnerCharacter->GetDeBuffResistRatio();

	Duration = Duration * (1.0f - DeBuffResistRatio);
}
