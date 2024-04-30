// Fill out your copyright notice in the Description page of Project Settings.


#include "UIUnitWidget.h"

void UUIUnitWidget::InitUnit(ABaseGameMode* gameMode)
{
	if (gameMode)
	{
		GameMode = gameMode;
		UIMgr = gameMode->UIMgr;
	}

	CacheOwnUI();
}

bool UUIUnitWidget::IsValidWidget()
{
	return bValidWidget;
}

void UUIUnitWidget::Show(bool isVisible)
{
	if (isVisible)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}
