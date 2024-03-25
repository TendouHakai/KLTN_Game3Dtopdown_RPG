// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "BattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UBattleWidget : public UUIWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
};
