// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuff.h"
#include "DamageBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UDamageBuff : public UBaseBuff
{
	GENERATED_BODY()
public:
	UDamageBuff();

	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo) override;

	UFUNCTION(BlueprintCallable, Category = "DamageBuff")
	float GetAdditionalDamPercent(bool bMagicDamage, ABaseCharacter* Attacker = nullptr) { return CalculateDamPercent(bMagicDamage, Attacker); }

	virtual float CalculateDamPercent(bool bMagicDamage, ABaseCharacter* Attacker) { return 0.0f; }
	virtual float GetBuffAmount() override { return InfluenceAmount; }
	virtual void CopyBuff(const UBaseBuff* OriginBuff) override;

protected:
	void InitInfluenceAmount(const FHeroBuffInfo& BuffInfo);

protected:
	float InfluenceAmount;
	int32  DamageBuffType;
};
