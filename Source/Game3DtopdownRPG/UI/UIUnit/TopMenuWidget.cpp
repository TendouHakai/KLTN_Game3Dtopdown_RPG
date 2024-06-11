// Fill out your copyright notice in the Description page of Project Settings.


#include "TopMenuWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"

void UTopMenuWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	textEnergy = GetOwnUI<UTextBlock>(TEXT("TextBlock_Energy"));
	textGold = GetOwnUI<UTextBlock>(TEXT("TextBlock_Gold"));
}

void UTopMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTopMenuWidget::Update()
{
	Super::Update();

	textEnergy->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), GetMgr(UItemMgr)->GetEnergy(), GetMgr(UItemMgr)->GetMaxEnergy())));
	textGold->SetText(FText::AsNumber(GetMgr(UItemMgr)->GetGold()));
}
