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
	ImageBackground = GetOwnUI<UImage>(TEXT("Image_Back"));
	ImageEffect = GetOwnUI<UImage>(TEXT("Image_Effect"));
	ImageItem = GetOwnUI<UImage>(TEXT("Image_Item"));
	textCount = GetOwnUI<UTextBlock>(TEXT("TextBlock_count"));
	OverlayCount = GetOwnUI<UOverlay>(TEXT("Overlay_Count"));

	SelectAnimation = GetWidgetAnimation(TEXT("Ani_Select"));
	ReleaseAnimation = GetWidgetAnimation(TEXT("Ani_Release"));

	if (gameItemInfo.m_ItemRecKey == 0) EmptyUI();
}

void UInventoryEquipContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryEquipContainerWidget::SetInfo(FGameItemInfo& GameItemInfo)
{
	this->gameItemInfo = GameItemInfo;
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(GameItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;

	SetImageItem(record->IconName);
	SetTextCount(gameItemInfo.m_ItemCount);
	SetFrameBackground(record->EquipmentGrape);
}

void UInventoryEquipContainerWidget::SetInfo(UInventoryEquipContainerWidget* InventoryContainerWidget)
{
	this->gameItemInfo = InventoryContainerWidget->GetGameItemInfo();
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(gameItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;

	SetImageItem(record->IconName);
	SetTextCount(gameItemInfo.m_ItemCount);
	SetFrameBackground(record->EquipmentGrape);
}

void UInventoryEquipContainerWidget::SetInfo(int32 itemreckey)
{
	IsInteract = false;
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(itemreckey)));
	if (nullptr == record) return;

	SetImageItem(record->IconName);
	SetTextCount(0);
	SetFrameBackground(record->EquipmentGrape);
}

void UInventoryEquipContainerWidget::EmptyUI()
{
	if (nullptr == ImageFrame || nullptr == ImageItem || nullptr == ImageBackground || nullptr == OverlayCount) return;

	SetImageItem("");
	SetTextCount(0);
	SetFrameBackground(EItemGrade::Max);
}

void UInventoryEquipContainerWidget::OnTap()
{
	if (IsInteract == false) return;
}

void UInventoryEquipContainerWidget::OnHover()
{
	StopAnimation(SelectAnimation);
	if (nullptr == SelectAnimation) return;
	ImageEffect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PlayAnimation(SelectAnimation);
}

void UInventoryEquipContainerWidget::OnUnHover()
{
	StopAnimation(SelectAnimation);
	if (nullptr == ReleaseAnimation) return;
	ImageEffect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PlayAnimation(ReleaseAnimation);
}

void UInventoryEquipContainerWidget::SetImageItem(FString ItemName)
{
	if (ItemName.IsEmpty())
	{
		ImageItem->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2D(ItemName, EGameTextureType::ItemEquipment);
	if (nullptr == ImageItem) return;
	if (nullptr == Tex)
	{
		ImageItem->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	ImageItem->SetBrushFromTexture(Tex);
	ImageItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInventoryEquipContainerWidget::SetTextCount(int32 count)
{
	if (nullptr == OverlayCount || nullptr == textCount) return;
	if (nullptr == textCount || count <= 0 || IsInteract == false)
	{
		OverlayCount->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	textCount->SetText(FText::AsNumber(count));
	OverlayCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInventoryEquipContainerWidget::SetFrameBackground(EItemGrade grade)
{
	if (nullptr == ImageBackground || nullptr == ImageFrame) return;
	FString PathFrame;

	switch (grade)
	{
	case EItemGrade::Normal:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_ItemEquipment_Grade_Normal.Frame_ItemEquipment_Grade_Normal";
		break;
	case EItemGrade::High:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_ItemEquipment_Grade_High.Frame_ItemEquipment_Grade_High";
		break;
	case EItemGrade::Rare:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_ItemEquipment_Grade_Rare.Frame_ItemEquipment_Grade_Rare";
		break;
	case EItemGrade::Hero:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_ItemEquipment_Grade_Hero.Frame_ItemEquipment_Grade_Hero";
		break;
	case EItemGrade::Legend:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_ItemEquipment_Grade_Legend.Frame_ItemEquipment_Grade_Legend";
		break;
	case EItemGrade::Max:
		PathFrame = "/Game/UI/Sprites/Components/Frame/frame_iconframe_square_01_Demo_n.frame_iconframe_square_01_Demo_n";
		break;
	default:
		break;
	}

	UTexture2D* TexFrame = GetMgr(UAssetMgr)->LoadTexture2DFromPath(PathFrame);

	if (nullptr == TexFrame)
	{
		ImageFrame->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ImageFrame->SetBrushFromTexture(TexFrame);
		ImageFrame->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (grade == EItemGrade::Max)
	{
		ImageBackground->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		setColorBackground(grade);
		ImageBackground->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
