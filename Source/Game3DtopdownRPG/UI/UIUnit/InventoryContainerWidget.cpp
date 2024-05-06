// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryContainerWidget.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"


void UInventoryContainerWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	ImageEffect = GetOwnUI<UImage>(TEXT("Image_Effect"));
	ImageBackground = GetOwnUI<UImage>(TEXT("Image_Background"));
	ImageFrame = GetOwnUI<UImage>(TEXT("Image_frame"));
	ImageItem = GetOwnUI<UImage>(TEXT("Image_Item"));
	OverlayCount = GetOwnUI<UOverlay>(TEXT("Overlay_Count"));
	TextCount = GetOwnUI<UTextBlock>(TEXT("TextBlock_count"));

	SelectAnimation = GetWidgetAnimation(TEXT("Ani_Select"));

	if (nullptr == gameItemInfo) EmptyUI();
}

void UInventoryContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
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


	itemInfoRecord = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(gameItemInfo->m_ItemRecKey)));
	if (nullptr == itemInfoRecord) return;

	SetImageItem(itemInfoRecord->ItemIcon);
	SetTextCount(gameItemInfo->m_ItemCount);
}

void UInventoryContainerWidget::EmptyUI()
{
	FString path = "/Game/UI/Sprites/Components/Frame/Frame_ItemFrame01_Empty.Frame_ItemFrame01_Empty";
	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2DFromPath(path);

	if (nullptr == Tex) return;
	
	if (nullptr == ImageFrame || nullptr == ImageItem || nullptr == ImageBackground || nullptr == OverlayCount) return;
	ImageFrame->SetBrushFromTexture(Tex);
	ImageBackground->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryContainerWidget::OnTap()
{
}

void UInventoryContainerWidget::SetImageItem(FString ItemName)
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

void UInventoryContainerWidget::SetTextCount(int32 count)
{
	if (nullptr == TextCount || count <= 0)
	{
		OverlayCount->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
		
	TextCount->SetText(FText::AsNumber(count));
	OverlayCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
