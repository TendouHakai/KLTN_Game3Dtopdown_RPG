// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroEquipmentPage.h"
#include "UIUnit/ScrollWidget.h"
#include "UIUnit/InventoryEquipContainerWidget.h"
#include "UIUnit/EquipmentSlotWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"

void UHeroEquipmentPage::CacheOwnUI()
{
	Super::CacheOwnUI();


	ItemEquipmentContainer_SCroll = GetOwnUI<UScrollWidget>(TEXT("ScrollWidge_EquipmentContainer"));
	if (nullptr != ItemEquipmentContainer_SCroll)
	{
		ItemEquipmentContainer_SCroll->InitUnit(GameMode);
		ItemEquipmentContainer_SCroll->ChildUpdateEvent.BindUObject(this, &UHeroEquipmentPage::UpdateChildItemEquipment);
	}

	for (int indexTab = 0; indexTab < static_cast<int32>(EItemEquipPosition::Max); ++indexTab)
	{
		UEquipmentSlotWidget* slot = GetOwnUI<UEquipmentSlotWidget>(FString::Printf(TEXT("EquipmentSlotWidget_%d"), indexTab + 1));
		if (nullptr != slot)
		{
			slot->InitUnit(GameMode);
			EquipmentSlots.Emplace(slot);
		}
	}
}

void UHeroEquipmentPage::Update()
{
	Super::Update();

	m_CurrentItemArray.Empty();
	FGameItemInfo gameinfo;
	gameinfo.m_ItemRecKey = 1;
	gameinfo.m_ItemCount = 2;
	m_CurrentItemArray.Emplace(gameinfo);

	if (nullptr != ItemEquipmentContainer_SCroll) ItemEquipmentContainer_SCroll->SetChildCount(m_CurrentItemArray.Num());
}

void UHeroEquipmentPage::SetHeroCharacter(ABaseCharacter* herocharacter)
{
	if (nullptr == herocharacter) return;
	character = herocharacter;
	for (UEquipmentSlotWidget* slot : EquipmentSlots)
	{
		slot->SetHeroCharacter(character);
	}
}

void UHeroEquipmentPage::UpdateChildItem(UWidget* Child, int32 ChildDataIdx)
{

}

void UHeroEquipmentPage::UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryEquipContainerWidget* InventoryContainer = Cast<UInventoryEquipContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_CurrentItemArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_CurrentItemArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	InventoryContainer->SetButtonEventEx(this);
}

