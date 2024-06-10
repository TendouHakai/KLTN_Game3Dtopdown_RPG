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
	imageLock = GetOwnUI<UImage>(TEXT("Image_EquipmentLock"));
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
}

void UEquipmentSlotWidget::EquipItemToSlot(FGameItemEquipmentInfo iteminfo)
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)));

	if (nullptr == record) return;

	if (record->EquipPosition != EquipmentPosition && EquipmentPosition != EItemEquipPosition::All)
	{
		EmptyUI();
		return;
	}

	inventoryEquipment->SetInfo(iteminfo);
	inventoryEquipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UEquipmentSlotWidget::EmptyUI()
{
	inventoryEquipment->SetInfo(FGameItemEquipmentInfo());
	inventoryEquipment->SetVisibility(ESlateVisibility::Collapsed);
}

void UEquipmentSlotWidget::OnDropEvent(FGameItemEquipmentInfo info)
{
	if (info.m_ItemRecKey == 0) return;
	if (OwnerDropDelegateEx.IsBound())
	{
		EquipItemToSlot(info);
		OwnerDropDelegateEx.ExecuteIfBound(inventoryEquipment->GetGameItemInfo().m_ItemRecKey, this);
	}
}

void UEquipmentSlotWidget::Update()
{
	Super::Update();

	if (nullptr == character) return;
	setImageIcon();
	FHeroInfo heroinfo = character->GetHeroInfo();

	if (!heroinfo.m_Equip.IsValidIndex(static_cast<int32>(EquipmentPosition)))
	{
		EmptyUI();
		return;
	}
	if (heroinfo.m_Equip[static_cast<int32>(EquipmentPosition)].m_ItemRecKey == 0) 
	{
		EmptyUI();
		return;
	}
	EquipItemToSlot(heroinfo.m_Equip[static_cast<int32>(EquipmentPosition)]);
	//inventoryEquipment->SetInfo(heroinfo.m_Equip[static_cast<int32>(EquipmentPosition)]);
	//inventoryEquipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
		path = "/Game/UI/Sprites/Components/Icon/spiked-shoulder-armor.spiked-shoulder-armor";
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
		path = "/Game/UI/Sprites/Components/Icon/knapsack.knapsack";
		break;
	case EItemEquipPosition::Weapon:
		path = "/Game/UI/Sprites/Components/Icon/Weapon.Weapon";
		break;
	case EItemEquipPosition::Shield:
		if (nullptr == character)
		{
			imageLock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			return;
		}
		switch (character->GetCurrentHeroClass())
		{
		case EHeroClass::NoWeapon:
			imageLock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			return;
		case EHeroClass::SwordAndShield:
			path = "/Game/UI/Sprites/Components/Icon/Shield.Shield";
			break;
		case EHeroClass::Bow:
			path = "/Game/UI/Sprites/Components/Icon/spiral-arrow.spiral-arrow";
			break;
		case EHeroClass::DoubleSword:
			path = "/Game/UI/Sprites/Components/Icon/Weapon.Weapon";
			break;
		case EHeroClass::MagicWand:
			imageLock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			return;
		case EHeroClass::SingleSword:
			imageLock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			return;
		default:
			imageLock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			return;
		}
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
	imageLock->SetVisibility(ESlateVisibility::Collapsed);
}
