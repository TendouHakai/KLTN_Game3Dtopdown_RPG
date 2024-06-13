// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseDebuff.h"
#include "FreezeDeBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UFreezeDeBuff : public UBaseDebuff
{
	GENERATED_BODY()
public:
	virtual void BeginBuff() override;
	virtual void EndBuff(bool bForcedEnd = false) override;
	virtual void Tick(float DeltaTime) override;

	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Freezing; }

protected:
	virtual void RestoreActor();
	void ActorFreeze(float GlobalAnimRateScale);
};
