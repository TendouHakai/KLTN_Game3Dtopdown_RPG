// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseDebuff.h"
#include "DotDamageDebuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UDotDamageDebuff : public UBaseDebuff
{
	GENERATED_BODY()
public:
	UDotDamageDebuff();
	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;

	virtual void TimeEndFunction() override;
	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo) override;
	virtual void Tick(float DeltaTime) override;
	virtual bool CheckCrowdControl() override { return false; }

	virtual void UpdateDebuffResist() override;
	virtual const int32 GetRemainTime() override;

	void DamageOverTime();
	void Damage();

	FORCEINLINE virtual const float GetDuration() override { return DotPeriod; }
	FORCEINLINE virtual const float GetElapseTime() override { return PeriodElapseTime; }
protected:
	void GuildRaidException(float& DotDamage);

protected:
	float DotAmount;
	int DotPeriod;
	int RemainDotPeriod;

	float PeriodElapseTime;
	bool bMagicDamage = true;
};
