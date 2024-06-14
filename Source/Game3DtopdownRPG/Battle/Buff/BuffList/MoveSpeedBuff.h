// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimSpeedBuff.h"
#include "MoveSpeedBuff.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UMoveSpeedBuff : public UAnimSpeedBuff
{
	GENERATED_BODY()
public:
	virtual void BeginBuff() override;
	virtual void EndBuff(bool bForcedEnd = false) override;

	virtual float GetAnimSpeed() override;
};
