// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryEquipContainerWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"

void UInventoryEquipContainerWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	ImageFrame = GetOwnUI<UImage>(TEXT("Image_Frame"));
	ImageBack = GetOwnUI<UImage>(TEXT("Image_Back"));
	ImageEffect = GetOwnUI<UImage>(TEXT("Image_Effect"));
	ImageItem = GetOwnUI<UImage>(TEXT("Image_Item"));
	textCount = GetOwnUI<UTextBlock>(TEXT("TextBlock_count"));
}

void UInventoryEquipContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CacheOwnUI();
}

void UInventoryEquipContainerWidget::SetInfo(FGameItemInfo& GameItemInfo)
{
	GameItemInfo = GameItemInfo;
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(GameItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;


}

void UInventoryEquipContainerWidget::SetInfo(FItemEquipmentInfoRecord* InventoryContainerWidget)
{

}

void UInventoryEquipContainerWidget::SetImageItem(FString ItemName)
{
	if (ItemName.IsEmpty())
	{
		ImageItem->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2D(ItemName, EGameTextureType::Item);
	if (nullptr == Tex || nullptr == ImageItem)
	{
		ImageItem->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	ImageItem->SetBrushFromTexture(Tex);
	ImageItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInventoryEquipContainerWidget::SetTextCount(int32 count)
{
	if (nullptr == textCount || count <= 0)
	{
		//OverlayCount->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	textCount->SetText(FText::AsNumber(count));
	//OverlayCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInventoryEquipContainerWidget::SetFrameBackground(EItemGrade grade)
{

}
