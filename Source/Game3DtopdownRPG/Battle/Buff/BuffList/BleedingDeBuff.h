// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DotDamageDebuff.h"
#include "BleedingDeBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UBleedingDeBuff : public UDotDamageDebuff
{
	GENERATED_BODY()
public:
	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Bleeding; }

	static float BleedingDebuffHealSubtraction;
};
