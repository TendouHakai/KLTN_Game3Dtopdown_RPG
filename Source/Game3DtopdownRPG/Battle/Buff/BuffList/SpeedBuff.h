// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuff.h"
#include "SpeedBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API USpeedBuff : public UBaseBuff
{
	GENERATED_BODY()
public:
	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;

	float GetUpdateSpeed();

	virtual float GetBuffAmount() override { return SpeedPercent; }

protected:
	float SpeedPercent;
};
