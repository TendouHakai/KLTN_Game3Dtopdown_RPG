// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseDebuff.h"
#include "SlowDebuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API USlowDebuff : public UBaseDebuff
{
	GENERATED_BODY()
public:
	virtual void BeginBuff() override;
	virtual void EndBuff(bool bForcedEnd /* = false */) override;

	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	float GetUpdateSpeed();

	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Slow; }

	virtual float GetBuffAmount() override { return bActiveBuff == true? SpeedPercent : 0.f; }

	static float GetSlowDebuffSpeed() { return -0.5f; }
protected:
	float SpeedPercent;
};
