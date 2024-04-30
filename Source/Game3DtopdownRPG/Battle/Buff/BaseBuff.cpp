// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"

UBaseBuff::UBaseBuff() : bIsPassiveBuff(false), Duration (0.0f), ElapseTime(0.0f), CasterCharacter(nullptr)
						,bActiveBuff(false), bDuplicated(false), OneSecondElapseTime(0.0f)
{
}

void UBaseBuff::InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	HeroBuffInfo = CheckBuffInfo;
	CasterCharacter = Caster;

	Duration = HeroBuffInfo.Duration;
	CurrentStack = 1;

	MaxStack = FMath::Max(1, HeroBuffInfo.BuffMaxStack);

	if (0 >= HeroBuffInfo.Duration)
		bIsPassiveBuff = true;

	SetBuffInfoText();
}

void UBaseBuff::BeginBuff()
{
	bActiveBuff = true;

}

void UBaseBuff::EndBuff(bool bForcedEnd)
{
	bActiveBuff = false;

	if (UpdateBuffInfoCallBack.IsBound())
	{
		UpdateBuffInfoCallBack.Unbind();
	}

	if (true == bForcedEnd) return;
	OnEndBuffCallBack.Broadcast(this);
}

void UBaseBuff::TimeEndFunction()
{
	EndBuff();
}

void UBaseBuff::RenewBuff(const FHeroBuffInfo& RenewBuffInfo)
{
	ElapseTime = 0.0f;
}

void UBaseBuff::Tick(float DeltaTime)
{
	if (true == bIsPassiveBuff || false == bActiveBuff)
		return;

	ElapseTime += DeltaTime;
	OneSecondElapseTime += DeltaTime;

	if (OneSecond <= OneSecondElapseTime)
	{
		OneSecondElapseTime = 0.f;
		UpdateBuffInfo();
	}

	if (ElapseTime >= Duration)
	{
		TimeEndFunction();
	}
}

bool UBaseBuff::IsSameBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo)
{
	if (Caster != CasterCharacter)
		return false;

	if (HeroBuffInfo.BuffType != CheckBuffInfo.BuffType)
		return false;

	if (HeroBuffInfo.BuffCondition != CheckBuffInfo.BuffCondition)
		return false;

	if (HeroBuffInfo.Duration != CheckBuffInfo.Duration)
		return false;

	if (HeroBuffInfo.BuffMaxStack != CheckBuffInfo.BuffMaxStack)
		return false;

	if (HeroBuffInfo.BuffAmount.Num() != CheckBuffInfo.BuffAmount.Num())
		return false;

	for (int i = 0; i < HeroBuffInfo.BuffAmount.Num(); ++i)
	{
		if (HeroBuffInfo.BuffAmount[i] != CheckBuffInfo.BuffAmount[i])
			return false;
	}

	return true;
}

const int32 UBaseBuff::GetRemainTime()
{
	int32 DurationAsInt = FMath::RoundToInt(GetDuration());
	int32 RemainSecsAsInt = DurationAsInt - FMath::RoundToInt(GetElapseTime());

	return FMath::Clamp(RemainSecsAsInt, 0, DurationAsInt);
}

void UBaseBuff::SetBuffInfoText()
{
	// chua co data
}

void UBaseBuff::UpdateBuffInfo()
{
	if (nullptr == OwnerCharacter) return;
	UpdateBuffInfoCallBack.ExecuteIfBound(this);
}
