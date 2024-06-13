// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuff.h"
#include "HealBuff.generated.h"

UCLASS(Blueprintable)
class GAME3DTOPDOWNRPG_API UHealBuff : public UBaseBuff
{
	GENERATED_BODY()
public:
	UHealBuff();

	virtual void InitBuff(ABaseCharacter* Caster, const FHeroBuffInfo& CheckBuffInfo) override;
	virtual void BeginBuff() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "HealBuff")
	void CharacterHeal(const ABaseCharacter* TargetCharacter, float InHealAmount);

	UFUNCTION(BlueprintCallable, Category = "HealBuff")
	bool IsSelfHeal();

	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Rec_HealthPoint; }

	FORCEINLINE virtual const float GetDuration() override { return 1.f; }

	virtual void RenewBuff(const FHeroBuffInfo& RenewBuffInfo) override;

protected:
	virtual float GetHealPercent();
	void Heal();
	void GuildRaidExcept(float& HealPercent);
	void BleedingDebuffHealSubtraction(float& HealPercent);
	void HealingRecoveryDecrease(float& HealPercent);
	void HealingRecoveryIncrease(float& HealPercent);

protected:
	float HealAmount;
	EBuffTargetType  HealTarget;
};
