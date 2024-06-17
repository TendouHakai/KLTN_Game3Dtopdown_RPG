// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryContainerWidget.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"


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
	ReleaseAnimation = GetWidgetAnimation(TEXT("Ani_Release"));

	OverlayUseCount = GetOwnUI<UOverlay>(TEXT("Overlay_UseCount"));
	TextUseCount = GetOwnUI<UTextBlock>(TEXT("TextBlock_UseCount"));

	OverlatInventoryLocation = GetOwnUI<UOverlay>(TEXT("Overlay_InventoryLocation"));
	imageinventoryLocation = GetOwnUI<UImage>(TEXT("Image_InventoryLocation"));

	if (gameItemInfo.m_ItemRecKey == 0) EmptyUI();
}

void UInventoryContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CacheOwnUI();
}

void UInventoryContainerWidget::SetInfo(FGameItemInfo& GameItemInfo, FItemInfoRecord* ItemInfoRecord)
{
	if (nullptr == ItemInfoRecord) return;
	gameItemInfo = GameItemInfo;
	itemInfoRecord = ItemInfoRecord;

	SetImageItem(itemInfoRecord->ItemIcon);
	SetTextCount(gameItemInfo.m_ItemCount);
}

void UInventoryContainerWidget::SetInfo(FGameItemInfo GameItemInfo)
{
	gameItemInfo = GameItemInfo;

	itemInfoRecord = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(gameItemInfo.m_ItemRecKey)));
	if (nullptr == itemInfoRecord) return;

	SetImageItem(itemInfoRecord->ItemIcon);
	SetTextCount(gameItemInfo.m_ItemCount);
	SetFrameBackground(itemInfoRecord->ItemGrape);
	SetInventoryLocation(gameItemInfo.m_InventoryLocation);
	OverlayUseCount->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryContainerWidget::SetInfo(UInventoryContainerWidget* InventoryContainerWidget)
{
	if (nullptr == InventoryContainerWidget) return;
	gameItemInfo = InventoryContainerWidget->GetGameItemInfo();

	itemInfoRecord = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(gameItemInfo.m_ItemRecKey)));
	if (nullptr == itemInfoRecord) return;

	SetImageItem(itemInfoRecord->ItemIcon);
	SetTextCount(gameItemInfo.m_ItemCount);
	SetFrameBackground(itemInfoRecord->ItemGrape);
	SetInventoryLocation(gameItemInfo.m_InventoryLocation);
	OverlayUseCount->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryContainerWidget::EmptyUI()
{
	if (nullptr == ImageFrame || nullptr == ImageItem || nullptr == ImageBackground || nullptr == OverlayCount) return;
	
	SetImageItem("");
	SetTextCount(-1);
	SetFrameBackground(EItemGrade::Max);
	ShowInventoryLocation(false);
	OverlayUseCount->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryContainerWidget::OnTap()
{
	if (!OwnerDelegateEx.IsBound()) return;
	if (false == IsInteract) return;
	OwnerDelegateEx.ExecuteIfBound(gameItemInfo.m_ItemRecKey, this);
}

void UInventoryContainerWidget::OnTapUseSubtract()
{
	if (!OwnerUseSubtractDelegateEx.IsBound()) return;
	if (false == IsInteract) return;
	OwnerUseSubtractDelegateEx.ExecuteIfBound(gameItemInfo.m_ItemRecKey, this);
}

void UInventoryContainerWidget::OnHover()
{
	StopAnimation(SelectAnimation);
	if (nullptr == SelectAnimation) return;
	ImageEffect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PlayAnimation(SelectAnimation);
}

void UInventoryContainerWidget::OnUnHover()
{
	StopAnimation(SelectAnimation);
	if (nullptr == ReleaseAnimation) 
		return;
	ImageEffect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PlayAnimation(ReleaseAnimation);
}

void UInventoryContainerWidget::OnDropEvent(FGameItemInfo info)
{
	if (info.m_ItemRecKey == 0) return;

	if (OwnerDropDelefateEx.IsBound())
	{
		SetInfo(info);
		OwnerDropDelefateEx.ExecuteIfBound(info.m_ItemRecKey, this);
	}
}

void UInventoryContainerWidget::OnCtrlTapEvent()
{
	if (OwnerCtrlTapDelegateEx.IsBound())
	{
		OwnerCtrlTapDelegateEx.ExecuteIfBound(gameItemInfo.m_ItemRecKey, this);
	}
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
	if (nullptr == TextCount || count < 0)
	{
		OverlayCount->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
		
	TextCount->SetText(FText::AsNumber(count));
	OverlayCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInventoryContainerWidget::SetInventoryLocation(EInventoryLocation location)
{
	FString PathIcon = "";

	switch (gameItemInfo.m_InventoryLocation)
	{
	default:
		break;
	case EInventoryLocation::InInventory:
		PathIcon = "/Game/UI/Sprites/Components/Icon/wooden-crate.wooden-crate";
		break;
	case EInventoryLocation::InBackpack:
		PathIcon = "/Game/UI/Sprites/Components/Icon/knapsack.knapsack";
		break;
	case EInventoryLocation::InEquipment:
		PathIcon = "/Game/UI/Sprites/Components/Icon/brutal-helm.brutal-helm";
		break;
	case EInventoryLocation::All:
		break;
	case EInventoryLocation::Max:
		break;
	}

	UTexture2D* TexIcon = GetMgr(UAssetMgr)->LoadTexture2DFromPath(PathIcon);

	if (nullptr == TexIcon)
	{
		imageinventoryLocation->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else
	{
		imageinventoryLocation->SetBrushFromTexture(TexIcon);
		imageinventoryLocation->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UInventoryContainerWidget::SetTextCountPerNumber(int32 number)
{
	if (nullptr == TextCount || number <= 0)
	{
		OverlayCount->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	FGameItemInfo iteminfo = GetMgr(UItemMgr)->FindItem(gameItemInfo.m_ItemRecKey);
	if (iteminfo.m_ItemRecKey == 0)
	{
		OverlayCount->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	TextCount->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), iteminfo.m_ItemCount, number)));
}

void UInventoryContainerWidget::ShowInventoryLocation(bool IsShow)
{
	if (IsShow)
	{
		OverlatInventoryLocation->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		OverlatInventoryLocation->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventoryContainerWidget::SetFrameBackground(EItemGrade grade)
{
	FString PathFrame = "";
	FString PathFrameBackgroud = "";

	switch (grade)
	{
	case EItemGrade::Normal:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_Item_Grade_Normal.Frame_Item_Grade_Normal";
		PathFrameBackgroud = "/Game/UI/Sprites/Components/Frame/Frame_Item_Background_Normal.Frame_Item_Background_Normal";
		break;
	case EItemGrade::High:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_Item_Grade_High.Frame_Item_Grade_High";
		PathFrameBackgroud = "/Game/UI/Sprites/Components/Frame/Frame_Item_Background_High.Frame_Item_Background_High";
		break;
	case EItemGrade::Rare:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_Item_Grade_Rare.Frame_Item_Grade_Rare";
		PathFrameBackgroud = "/Game/UI/Sprites/Components/Frame/Frame_Item_Background_Rare.Frame_Item_Background_Rare";
		break;
	case EItemGrade::Hero:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_Item_Grade_Hero.Frame_Item_Grade_Hero";
		PathFrameBackgroud = "/Game/UI/Sprites/Components/Frame/Frame_Item_Background_Hero.Frame_Item_Background_Hero";
		break;
	case EItemGrade::Legend:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_Item_Grade_Legend.Frame_Item_Grade_Legend";
		PathFrameBackgroud = "/Game/UI/Sprites/Components/Frame/Frame_Item_background_Legend.Frame_Item_background_Legend";
		break;
	case EItemGrade::Max:
		PathFrame = "/Game/UI/Sprites/Components/Frame/Frame_ItemFrame01_Empty.Frame_ItemFrame01_Empty";
		break;
	default:
		break;
	}

	UTexture2D* TexFrame = GetMgr(UAssetMgr)->LoadTexture2DFromPath(PathFrame);

	if (nullptr == TexFrame) 
	{ 
		ImageFrame->SetVisibility(ESlateVisibility::Hidden);
		return; 
	}
	else
	{
		ImageFrame->SetBrushFromTexture(TexFrame);
		ImageFrame->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (PathFrameBackgroud.IsEmpty())
	{
		ImageBackground->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UTexture2D* TexFrameBackgroud = GetMgr(UAssetMgr)->LoadTexture2DFromPath(PathFrameBackgroud);
		if (nullptr == TexFrameBackgroud) 
		{
			ImageBackground->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			ImageBackground->SetBrushFromTexture(TexFrameBackgroud);
			ImageBackground->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

void UInventoryContainerWidget::SetUseCount(int32 count)
{
	if (nullptr == OverlayUseCount) return;
	if (nullptr == TextUseCount) return;

	if (count <= 0)
	{
		OverlayUseCount->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (count >= gameItemInfo.m_ItemCount) count = gameItemInfo.m_ItemCount;

	OverlayUseCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	TextUseCount->SetText(FText::AsNumber(count));
}

void UInventoryContainerWidget::HideEffect()
{
	ImageBackground->SetVisibility(ESlateVisibility::Hidden);
}
