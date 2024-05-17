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

	for (int indexSlot = 0; indexSlot < static_cast<int32>(EItemEquipPosition::Max); ++indexSlot)
	{
		UEquipmentSlotWidget* slot = GetOwnUI<UEquipmentSlotWidget>(FString::Printf(TEXT("EquipmentSlotWidget_%d"), indexSlot));
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

	m_CurrentItemEquipmentArray.Empty();
	FGameItemEquipmentInfo gameinfo;
	gameinfo.m_ItemRecKey = 1;
	gameinfo.m_ItemUgrapeLevel = 2;

	FGameItemEquipmentInfo gameinfo1;
	gameinfo1.m_ItemRecKey = 2;
	gameinfo1.m_ItemUgrapeLevel = 0;
	m_CurrentItemEquipmentArray.Emplace(gameinfo);
	m_CurrentItemEquipmentArray.Emplace(gameinfo1);

	if (nullptr != ItemEquipmentContainer_SCroll) ItemEquipmentContainer_SCroll->SetChildCount(m_CurrentItemEquipmentArray.Num());
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
	if (!m_CurrentItemEquipmentArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemEquipmentInfo info = m_CurrentItemEquipmentArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	InventoryContainer->SetButtonEventEx(this);
}

