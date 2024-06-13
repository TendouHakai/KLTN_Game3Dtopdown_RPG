// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuff.h"
#include "HealBuff.h"
#include "PeriodHealBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UPeriodHealBuff : public UHealBuff
{
	GENERATED_BODY()
public:
	UPeriodHealBuff();

	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual void BeginBuff() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "PeriodHealBuff")
	void PeriodHeal();

	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Rec_HealthPoint_Loop; }
	virtual void TimeEndFunction() override;
	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo) override;

	FORCEINLINE virtual const float GetDuration() override { return HealPeriod; }
	FORCEINLINE virtual const float GetElapseTime() override { return PeriodElapseTime; }
	virtual float GetBuffAmount() override { return HealAmount; }

protected:
	int32 HealPeriod;
	int32 RemainHealPeriod;

	float PeriodElapseTime;
};
