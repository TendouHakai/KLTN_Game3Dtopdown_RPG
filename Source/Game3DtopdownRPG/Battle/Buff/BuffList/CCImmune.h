// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseBuff.h"
#include "CCImmune.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UCCImmune : public UBaseBuff
{
	GENERATED_BODY()
public:
	virtual int32 BuffStateIndex() override { return (int32)EBuffEffectType::Immune; }
};
