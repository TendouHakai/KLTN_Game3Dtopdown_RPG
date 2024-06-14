// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimSpeedBuff.h"
#include "AttackSpeedBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UAttackSpeedBuff : public UAnimSpeedBuff
{
	GENERATED_BODY()
public:
	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Inc_AtkSpeed; }
	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo) override;
	virtual float GetAnimSpeed() override;
};
