// Fill out your copyright notice in the Description page of Project Settings.


#include "MsgBoxReward.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryEquipContainerWidget.h"

bool UMsgBoxReward::Initialize()
{
	bool bInitialize = Super::Initialize();
	if (bInitialize)
	{
		sizebox_ScrollItemWidget = GetOwnUI<USizeBox>(TEXT("SizeBox_ScrollItemWidget"));
		sizebox_ScrollItemEquipWidget = GetOwnUI<USizeBox>(TEXT("SizeBox_ScrollItemEquipmentWidget"));
		ScrollItemWidget = GetOwnUI<UScrollWidget>(TEXT("ScrollWidgetBP"));
		ScrollItemEquipWidget = GetOwnUI<UScrollWidget>(TEXT("ScrollWidgetBP_ItemEquipment"));
	}
	return bInitialize;
}

void UMsgBoxReward::SetInfo(TArray<FGameItemInfo>& gameinfos)
{
	items = gameinfos;
	if (nullptr != ScrollItemWidget)
	{
		ScrollItemWidget->VisibleRowCnt = 1;
		ScrollItemWidget->ChildCntPerRow = gameinfos.Num();
		ScrollItemWidget->InitUnit(GameMode);
		ScrollItemWidget->ChildUpdateEvent.BindUObject(this, &UMsgBoxReward::UpdateChildItem);
		ScrollItemWidget->SetChildCount(gameinfos.Num());

		sizebox_ScrollItemWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		sizebox_ScrollItemEquipWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMsgBoxReward::SetInfo(TArray<FGameItemEquipmentInfo>& gameinfos)
{
	itemEquips = gameinfos;
	if (nullptr != ScrollItemWidget)
	{
		ScrollItemEquipWidget->VisibleRowCnt = 1;
		ScrollItemEquipWidget->ChildCntPerRow = gameinfos.Num();
		ScrollItemEquipWidget->InitUnit(GameMode);
		ScrollItemEquipWidget->ChildUpdateEvent.BindUObject(this, &UMsgBoxReward::UpdateChildItemEquipment);
		ScrollItemEquipWidget->SetChildCount(gameinfos.Num());

		sizebox_ScrollItemWidget->SetVisibility(ESlateVisibility::Collapsed);
		sizebox_ScrollItemEquipWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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

void UMsgBoxReward::UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryEquipContainerWidget* InventoryEquipContainer = Cast<UInventoryEquipContainerWidget>(Child);

	if (nullptr == InventoryEquipContainer) return;
	if (!itemEquips.IsValidIndex(ChildDataIdx)) return;

	FGameItemEquipmentInfo info = itemEquips[ChildDataIdx];

	InventoryEquipContainer->SetInfo(info);
	InventoryEquipContainer->SetTextCount(info.m_ItemUgrapeLevel);
}
