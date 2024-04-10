// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget.h"

void UUIWidget::Init()
{
	Super::Init();
}

void UUIWidget::Init(ABaseGameMode* InGameMode)
{
	if (InGameMode != nullptr)
	{
		GameMode = InGameMode;
		UIMgr = GameMode->UIMgr;
		Init();
	}
}

void UUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIWidget::Destroy(UUIBaseMgr* InUIManager)
{
	Super::Destroy(InUIManager);
}

void UUIWidget::OnOpen(bool Immediately /*= false*/)
{
	OnOpenBP();
}

void UUIWidget::OnClose(bool Immediately /*= false*/)
{
	OnCloseBP();
	Destroy(UIMgr);
}
