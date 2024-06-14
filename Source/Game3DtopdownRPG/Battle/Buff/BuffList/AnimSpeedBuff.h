// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpeedBuff.h"
#include "AnimSpeedBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UAnimSpeedBuff : public USpeedBuff
{
	GENERATED_BODY()
public:
	virtual void ApplyOwnerSpeed(float Speed);
	virtual void BeginBuff() override;
	virtual void EndBuff(bool bForcedEnd = false) override;

	float CalculateSpeedBuffAmount(const UClass* ClassType);

	virtual float GetAnimSpeed() { return 1.0f; }

protected:
	bool IsFreezeState();
	virtual void UpdateAnimSpeed();

private:
	void SetChildActorGlobalAnimRateScale(float Speed);
};
