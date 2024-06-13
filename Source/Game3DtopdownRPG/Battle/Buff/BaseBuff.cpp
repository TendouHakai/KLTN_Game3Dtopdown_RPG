// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Util/Managers/HeroBuffMgr.h"
#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "CoreMinimal.h"

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

void UBaseBuff::CopyBuff(const UBaseBuff* OriginBuff)
{
	if (false == IsValid(OriginBuff))
		return;

	Duration = OriginBuff->Duration;
	ElapseTime = OriginBuff->ElapseTime;
	CurrentStack = OriginBuff->CurrentStack;
	OwnerCharacter = OriginBuff->OwnerCharacter;
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

bool UBaseBuff::HasOwnerOnlyOneBuffOfThis()
{
	TArray<UBaseBuff*> buffArray;
	OwnerCharacter->FindHaveBuff(GetClass(), buffArray);

	int32 ActiveBuffCount = 0;
	for (UBaseBuff* BaseBuff : buffArray)
	{
		if (false == IsValid(BaseBuff))
			continue;

		if (BaseBuff->IsActive())
			++ActiveBuffCount;
	}

	return (1 < ActiveBuffCount) ? false : true;
}

const int32 UBaseBuff::GetRemainTime()
{
	int32 DurationAsInt = FMath::RoundToInt(GetDuration());
	int32 RemainSecsAsInt = DurationAsInt - FMath::RoundToInt(GetElapseTime());

	return FMath::Clamp(RemainSecsAsInt, 0, DurationAsInt);
}

bool UBaseBuff::IsNecessaryBuffActor()
{
	return true;
}

void UBaseBuff::SetBuffInfoText()
{
	FBuffInfoRecord* BuffInfoRecord = GetMgr(UHeroBuffMgr)->GetHeroBuffInfoRecord((int32)HeroBuffInfo.BuffType, HeroBuffInfo.BuffCondition);
	if (nullptr == BuffInfoRecord) return;

	FString bufftext = BuffInfoRecord->BuffText;

	wchar_t FormatStr[256]; 
	wcscpy_s(FormatStr, TCHAR_TO_WCHAR(*bufftext)); 

	if(HeroBuffInfo.BuffAmount.Num() == 1)
		bufftext = FString::Printf(FormatStr, HeroBuffInfo.BuffAmount[0]);
	else if (HeroBuffInfo.BuffAmount.Num() == 2)
		bufftext = FString::Printf(FormatStr, HeroBuffInfo.BuffAmount[0], HeroBuffInfo.BuffAmount[1]);
	else if(HeroBuffInfo.BuffAmount.Num() == 3)
		bufftext = FString::Printf(FormatStr, HeroBuffInfo.BuffAmount[0], HeroBuffInfo.BuffAmount[1], HeroBuffInfo.BuffAmount[2]);

	BuffInfoText = bufftext;
	//BuffInfoText = HeroBuffInfo
}

void UBaseBuff::UpdateBuffInfo()
{
	if (nullptr == OwnerCharacter) return;
	UpdateBuffInfoCallBack.ExecuteIfBound(this);
}

void UBaseBuff::ConvertToPercent(float& ConvertPercent)
{
	ConvertPercent = ConvertPercent * 0.01f;
}
