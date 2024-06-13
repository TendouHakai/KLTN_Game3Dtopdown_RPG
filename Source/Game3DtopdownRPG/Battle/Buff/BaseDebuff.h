// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "Game3DtopdownRPG/Battle/BaseAnimInstance.h"
#include "BaseDebuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UBaseDebuff : public UBaseBuff
{
	GENERATED_BODY()
public:
	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual void BeginBuff() override;
	virtual bool CheckCrowdControl() { return true; }
	virtual bool IsSameBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo) override;

	void UpdateFakeCCBuff();
	virtual void UpdateDebuffResist();

protected:
	EChrAnimState CastBuffAnimState;
};
