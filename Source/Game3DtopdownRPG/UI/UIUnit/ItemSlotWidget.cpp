// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

void UItemSlotWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	inventoryEquipment = GetOwnUI<UInventoryContainerWidget>(TEXT("MyInventoryContainerWidget"));
	if (nullptr != inventoryEquipment)
	{
		inventoryEquipment->InitUnit(GameMode);
	}
}

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CacheOwnUI();
}

void UItemSlotWidget::EquipItemToSlot(FGameItemInfo iteminfo)
{
	if (iteminfo.m_ItemRecKey == 0) return;
	//FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)));

	//if (nullptr == record) return;

	inventoryEquipment->SetInfo(iteminfo);
	inventoryEquipment->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UItemSlotWidget::EmptyUI()
{
	inventoryEquipment->SetVisibility(ESlateVisibility::Collapsed);
}

void UItemSlotWidget::OnDropEvent(FGameItemInfo info)
{
	if (info.m_ItemRecKey == 0) return;
	if (OwnerDropDelegateEx.IsBound())
	{
		EquipItemToSlot(info);
		OwnerDropDelegateEx.ExecuteIfBound(info.m_ItemRecKey, this);
	}
}

void UItemSlotWidget::OnTapEvent()
{
	if (OwnerTapDelegateEx.IsBound())
	{
		OwnerTapDelegateEx.ExecuteIfBound(0, this);
	}
}

void UItemSlotWidget::SetHeroCharacter(ABaseCharacter* hero)
{
	if (nullptr == hero) return;
	character = hero;
}

void UItemSlotWidget::Update()
{
	Super::Update();

	if (nullptr == character) return;
	FHeroInfo heroinfo = character->GetHeroInfo();

	if (!heroinfo.m_EquipNormal.IsValidIndex(EquipPosition))
	{
		EmptyUI();
		return;
	}
	if (heroinfo.m_EquipNormal[EquipPosition].m_ItemRecKey == 0)
	{
		EmptyUI();
		return;
	}
	EquipItemToSlot(heroinfo.m_EquipNormal[EquipPosition]);
}
