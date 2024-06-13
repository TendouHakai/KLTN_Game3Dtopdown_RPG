// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuff.h"
#include "ShieldBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UShieldBuff : public UBaseBuff
{
	GENERATED_BODY()
public:
	virtual void BeginBuff() override;
	virtual void EndBuff(bool bForcedEnd = false) override;
	virtual void Tick(float DeltaTime) override;
	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo);

	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Shield; }
};
