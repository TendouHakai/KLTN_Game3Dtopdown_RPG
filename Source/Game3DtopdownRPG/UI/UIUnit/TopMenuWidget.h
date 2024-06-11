// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/TextBlock.h"
#include "TopMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UTopMenuWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void Update() override;
protected:
	// UI
	UTextBlock* textEnergy;
	UTextBlock* textGold;

	// info
};
