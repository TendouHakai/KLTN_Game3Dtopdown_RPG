// Fill out your copyright notice in the Description page of Project Settings.


#include "MsgBoxReward.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryContainerWidget.h"

bool UMsgBoxReward::Initialize()
{
	bool bInitialize = Super::Initialize();
	if (bInitialize)
	{
		ScrollWidget = GetOwnUI<UScrollWidget>(TEXT("ScrollWidgetBP"));
	}
	return bInitialize;
}

void UMsgBoxReward::SetInfo(TArray<FGameItemInfo>& gameinfos)
{
	items = gameinfos;
	if (nullptr != ScrollWidget)
	{
		ScrollWidget->VisibleRowCnt = 1;
		ScrollWidget->ChildCntPerRow = gameinfos.Num();
		ScrollWidget->InitUnit(GameMode);

		ScrollWidget->ChildUpdateEvent.BindUObject(this, &UMsgBoxReward::UpdateChildItem);
	}
}

void UMsgBoxReward::UpdateChildItem(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!items.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = items[ChildDataIdx];

	InventoryContainer->SetInfo(info);
}
