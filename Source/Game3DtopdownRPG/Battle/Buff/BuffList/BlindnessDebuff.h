// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuff.h"
#include "BlindnessDebuff.generated.h"


UCLASS(Blueprintable)
class GAME3DTOPDOWNRPG_API UBlindnessDebuff : public UBaseBuff
{
	GENERATED_BODY()
public:
	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Blindness; }
	
	UFUNCTION( BlueprintPure, Category = "BlindnessDebuff" )
	virtual float GetBuffAmount() override { return BlindnessPercent; }

public:
	float BlindnessPercent;
};
