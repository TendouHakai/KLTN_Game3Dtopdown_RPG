// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPage.h"
#include "UIUnit/ScrollWidget.h"

void UInventoryPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	ItemContainer_SCroll = GetOwnUI<UScrollWidget>(TEXT("ScrollWidgetBP_ItemContainer"));
}

void UInventoryPage::Update()
{
	Super::Update();
}
