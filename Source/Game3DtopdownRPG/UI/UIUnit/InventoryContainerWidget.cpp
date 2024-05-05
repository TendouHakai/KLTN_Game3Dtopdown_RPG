// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryContainerWidget.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "Game3DtopdownRPG/Util/Managers/TableMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"


void UInventoryContainerWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	ImageItem = GetOwnUI<UImage>(TEXT("Image_Item"));
	SelectAnimation = GetWidgetAnimation(TEXT("Ani_Select"));
	TextCount = GetOwnUI<UTextBlock>(TEXT("TextBlock_count"));
}

void UInventoryContainerWidget::SetInfo(FGameItemInfo* GameItemInfo, FItemInfoRecord* ItemInfoRecord)
{
	if (nullptr == GameItemInfo || nullptr == ItemInfoRecord) return;
	gameItemInfo = GameItemInfo;
	itemInfoRecord = ItemInfoRecord;

	SetImageItem(itemInfoRecord->ItemIcon);
	SetTextCount(gameItemInfo->m_ItemCount);
}

void UInventoryContainerWidget::SetInfo(FGameItemInfo* GameItemInfo)
{
	if (nullptr == GameItemInfo) return;
	gameItemInfo = GameItemInfo;


	itemInfoRecord = GetMgr(UTableMgr)->GetItemInfoRecord(FName(FString::FromInt(gameItemInfo->m_ItemRecKey)));
	if (nullptr == itemInfoRecord) return;

	SetImageItem(itemInfoRecord->ItemIcon);
	SetTextCount(gameItemInfo->m_ItemCount);
}

void UInventoryContainerWidget::OnTap()
{
}

void UInventoryContainerWidget::SetImageItem(FString ItemName)
{
	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2D(ItemName, EGameTextureType::Item);
	if (nullptr == Tex || nullptr == ImageItem)
		return;
	ImageItem->SetBrushFromTexture(Tex);
}

void UInventoryContainerWidget::SetTextCount(int32 count)
{
	if (nullptr == TextCount || count<=0)
		return;
	TextCount->SetText(FText::AsNumber(count));
}
