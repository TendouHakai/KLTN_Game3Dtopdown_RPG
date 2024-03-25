// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "BattleHeroPortraitWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UBattleHeroPortraitWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
};
