// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "InventoryPage.generated.h"

class UInventoryContainerWidget;
class UScrollWidget;

UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

protected:
	UInventoryContainerWidget* CurrentSelectedItem;
	UScrollWidget* ItemContainer_SCroll;
};
