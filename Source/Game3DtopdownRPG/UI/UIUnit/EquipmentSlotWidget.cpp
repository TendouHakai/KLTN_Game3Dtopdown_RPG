// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlotWidget.h"
#include "InventoryEquipContainerWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/AssetMgr.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

void UEquipmentSlotWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	imageIcon = GetOwnUI<UImage>(TEXT("Image_Icon"));
	if (imageIcon != nullptr)
	{
		setImageIcon();
	}

	inventoryEquipment = GetOwnUI<UInventoryEquipContainerWidget>(TEXT("InventoryEquipmentContainerWidget"));
	if (inventoryEquipment != nullptr)
	{
		inventoryEquipment->InitUnit(GameMode);
	}
}

void UEquipmentSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEquipmentSlotWidget::SetHeroCharacter(ABaseCharacter* hero)
{
	if (nullptr == hero) return;
	character = hero;
	FHeroInfo heroinfo = character->GetHeroInfo();

	if (!heroinfo.m_Equip.IsValidIndex(static_cast<int32>(EquipmentPosition))) return;
	if (heroinfo.m_Equip[static_cast<int32>(EquipmentPosition)].m_ItemRecKey == 0);
	inventoryEquipment->SetInfo(heroinfo.m_Equip[static_cast<int32>(EquipmentPosition)]);
	inventoryEquipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UEquipmentSlotWidget::EquipItemToSlot(FGameItemEquipmentInfo iteminfo)
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)));

	if (record->EquipPosition != EquipmentPosition) return;
	inventoryEquipment->SetInfo(iteminfo);
	inventoryEquipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	character->EquipItem(iteminfo);
}

void UEquipmentSlotWidget::setImageIcon()
{
	FString path;
	switch (EquipmentPosition)
	{
	case EItemEquipPosition::HeadGears:
		path = "/Game/UI/Sprites/Components/Icon/HeadGears.HeadGears";
		break;
	case EItemEquipPosition::ShoulderPad:

		break;
	case EItemEquipPosition::Shoe:
		path = "/Game/UI/Sprites/Components/Icon/Shoe.Shoe";
		break;
	case EItemEquipPosition::Glove:
		path = "/Game/UI/Sprites/Components/Icon/Glove.Glove";
		break;
	case EItemEquipPosition::Belt:
		path = "/Game/UI/Sprites/Components/Icon/Belt.Belt";
		break;
	case EItemEquipPosition::Backpack:
		break;
	case EItemEquipPosition::Weapon:
		path = "/Game/UI/Sprites/Components/Icon/Weapon.Weapon";
		break;
	case EItemEquipPosition::Shield:
		path = "/Game/UI/Sprites/Components/Icon/Shield.Shield";
		break;
	case EItemEquipPosition::Clother:
		path = "/Game/UI/Sprites/Components/Icon/Clother.Clother";
	case EItemEquipPosition::Max:
		break;
	default:
		break;
	}

	UTexture2D* Tex = GetMgr(UAssetMgr)->LoadTexture2DFromPath(path);
	if (nullptr == Tex) return;
	imageIcon->SetBrushFromTexture(Tex);
}
