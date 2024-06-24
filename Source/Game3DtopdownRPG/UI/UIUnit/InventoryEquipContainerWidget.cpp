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
	textUpgradeLevel = GetOwnUI<UTextBlock>(TEXT("TextBlock_count"));
	OverlayUpgradeLevel = GetOwnUI<UOverlay>(TEXT("Overlay_Count"));

	SelectAnimation = GetWidgetAnimation(TEXT("Ani_Select"));
	ReleaseAnimation = GetWidgetAnimation(TEXT("Ani_Release"));

	OverlatInventoryLocation = GetOwnUI<UOverlay>(TEXT("Overlay_InventoryLocation"));
	imageinventoryLocation = GetOwnUI<UImage>(TEXT("Image_InventoryLocation"));

	OverlayHeroClass = GetOwnUI<UOverlay>(TEXT("Overlay_HeroClass"));
	imageHeroClass = GetOwnUI<UImage>(TEXT("Image_HeroClass"));

	if (gameItemInfo.m_ItemRecKey == 0) EmptyUI();
}

void UInventoryEquipContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryEquipContainerWidget::SetInfo(FGameItemEquipmentInfo GameItemInfo)
{
	this->gameItemInfo = GameItemInfo;
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(GameItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;

	SetImageItem(record->IconName);
	SetTextUpgrapeLevel(gameItemInfo.m_ItemUgrapeLevel);
	SetFrameBackground(record->EquipmentGrape);
	SetInventoryLocation(gameItemInfo.m_InventoryLocation);
	OverlayHeroClass->SetVisibility(ESlateVisibility::Collapsed);
	if (record->EquipPosition == EItemEquipPosition::Weapon)
		SetHeroClass(record->HeroClass);
}

void UInventoryEquipContainerWidget::SetInfo(UInventoryEquipContainerWidget* InventoryContainerWidget)
{
	this->gameItemInfo = InventoryContainerWidget->GetGameItemInfo();
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(gameItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;

	SetImageItem(record->IconName);
	SetTextUpgrapeLevel(gameItemInfo.m_ItemUgrapeLevel);
	SetFrameBackground(record->EquipmentGrape);
	SetInventoryLocation(gameItemInfo.m_InventoryLocation);
	OverlayHeroClass->SetVisibility(ESlateVisibility::Collapsed);
	if (record->EquipPosition == EItemEquipPosition::Weapon)
		SetHeroClass(record->HeroClass);
}

void UInventoryEquipContainerWidget::SetInfo(int32 itemreckey)
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(itemreckey)));
	if (nullptr == record) return;

	SetImageItem(record->IconName);
	SetTextUpgrapeLevel(0);
	SetFrameBackground(record->EquipmentGrape);
}

void UInventoryEquipContainerWidget::EmptyUI()
{
	if (nullptr == ImageFrame || nullptr == ImageItem || nullptr == ImageBackground || nullptr == OverlayUpgradeLevel) return;

	SetImageItem("");
	SetTextUpgrapeLevel(0);
	SetFrameBackground(EItemGrade::Max);
}

void UInventoryEquipContainerWidget::OnTap()
{
	if (OwnerDelegateEx.IsBound()) OwnerDelegateEx.ExecuteIfBound(gameItemInfo.m_ItemRecKey, this);
}

void UInventoryEquipContainerWidget::OnCtrlTap()
{
	if (OwnerCtrlTapDelegateEx.IsBound()) OwnerCtrlTapDelegateEx.ExecuteIfBound(gameItemInfo.m_ItemRecKey, this);
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

void UInventoryEquipContainerWidget::SetTextCountPerNumber(int32 number)
{
	if (nullptr == textUpgradeLevel || number <= 0)
	{
		OverlayUpgradeLevel->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	int32 itemcount = GetMgr(UItemMgr)->CountItemEqupiment(gameItemInfo.m_ItemRecKey);

	textUpgradeLevel->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), itemcount, number)));
	OverlayUpgradeLevel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInventoryEquipContainerWidget::SetTextCount(int32 number)
{
	if (nullptr == textUpgradeLevel || number <= 0)
	{
		OverlayUpgradeLevel->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	textUpgradeLevel->SetText(FText::FromString(FString::Printf(TEXT("x%d"), number)));
	OverlayUpgradeLevel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInventoryEquipContainerWidget::ShowInventoryLocation(bool IsShow)
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

void UInventoryEquipContainerWidget::ShowHeroClass(bool IsShow)
{
	if (gameItemInfo.m_ItemRecKey == 0) return;
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(gameItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;
	if (record->EquipPosition != EItemEquipPosition::Weapon) return;

	if (IsShow)
	{
		OverlayHeroClass->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		OverlayHeroClass->SetVisibility(ESlateVisibility::Collapsed);
	}
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

void UInventoryEquipContainerWidget::SetTextUpgrapeLevel(int32 level)
{
	if (nullptr == OverlayUpgradeLevel || nullptr == textUpgradeLevel) return;
	if (nullptr == textUpgradeLevel || level <= 0 || IsInteract == false)
	{
		OverlayUpgradeLevel->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	FString str = "+";
	str += FString::FromInt(level);
	
	textUpgradeLevel->SetText(FText::FromString(str));
	OverlayUpgradeLevel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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

void UInventoryEquipContainerWidget::SetInventoryLocation(EInventoryLocation location)
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

void UInventoryEquipContainerWidget::SetHeroClass(EHeroClass heroclass)
{
	FString PathIcon = "";

	switch (heroclass)
	{
	case EHeroClass::NoWeapon:
		break;
	case EHeroClass::SwordAndShield:
		PathIcon = "/Game/UI/Sprites/Components/Icon/templar-shield.templar-shield";
		break;
	case EHeroClass::Bow:
		PathIcon = "/Game/UI/Sprites/Components/Icon/high-shot.high-shot";
		break;
	case EHeroClass::DoubleSword:
		PathIcon = "/Game/UI/Sprites/Components/Icon/dervish-swords.dervish-swords";
		break;
	case EHeroClass::MagicWand:
		PathIcon = "/Game/UI/Sprites/Components/Icon/wizard-staff.wizard-staff";
		break;
	case EHeroClass::SingleSword:
		PathIcon = "/Game/UI/Sprites/Components/Icon/broad-dagger.broad-dagger";
		break;
	default:
		break;
	}

	UTexture2D* TexIcon = GetMgr(UAssetMgr)->LoadTexture2DFromPath(PathIcon);

	if (nullptr == TexIcon)
	{
		imageHeroClass->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else
	{
		imageHeroClass->SetBrushFromTexture(TexIcon);
		imageHeroClass->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
