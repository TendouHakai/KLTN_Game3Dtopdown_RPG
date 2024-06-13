// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseDebuff.h"
#include "StunDebuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UStunDebuff : public UBaseDebuff
{
	GENERATED_BODY()
public:
	virtual void BeginBuff() override;
	virtual void EndBuff(bool bForcedEnd = false) override;

	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Stun; }
};
