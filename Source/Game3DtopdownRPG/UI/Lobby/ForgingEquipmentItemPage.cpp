// Fill out your copyright notice in the Description page of Project Settings.


#include "ForgingEquipmentItemPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/EquipmentSlotWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryEquipContainerWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"

void UForgingEquipmentItemPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	ItemContainer_SCroll = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerItem"));
	if (nullptr != ItemContainer_SCroll)
	{
		ItemContainer_SCroll->InitUnit(GameMode);
		ItemContainer_SCroll->ChildUpdateEvent.BindUObject(this, &UForgingEquipmentItemPage::UpdateChildEquipmentItem);
	}

	ConsumeMaterials_SCroll = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ConsumeMaterials"));
	if (nullptr != ConsumeMaterials_SCroll)
	{
		ConsumeMaterials_SCroll->InitUnit(GameMode);
		ConsumeMaterials_SCroll->ChildUpdateEvent.BindUObject(this, &UForgingEquipmentItemPage::UpdateChildConsumeMaterials);
	}

	// Forging info item
	textName = GetOwnUI<UTextBlock>(TEXT("TextBlock_NameItem"));
	m_currentForgingItem = GetOwnUI<UEquipmentSlotWidget>(TEXT("EquipmentSlotWidget_CurrentForging"));
	if (nullptr != m_currentForgingItem)
	{
		m_currentForgingItem->InitUnit(GameMode);
		m_currentForgingItem->SetDropEventEx(this);
	}
	textCreateCountItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_CreateCountItem"));
	sliderCountItem = GetOwnUI<USlider>(TEXT("Slider_CountItem"));
	progressbarCountItem = GetOwnUI<UProgressBar>(TEXT("ProgressBar_CountItem"));
	textPrice = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesPriceItem"));

	// Consume materials
	m_PreviousItem = GetOwnUI<UEquipmentSlotWidget>(TEXT("EquipmentSlotWidget_PreviousItem"));
	if (nullptr != m_PreviousItem) m_PreviousItem->InitUnit(GameMode);
	Update();
}

void UForgingEquipmentItemPage::Update()
{
	Super::Update();

	m_EquipmentItemRecipeArray.Empty();
	//m_ConsumeMaterialArray.Empty();

	m_EquipmentItemRecipeArray = GetMgr(UItemMgr)->GetAllItemEquipmentRecipe();
	if (ItemContainer_SCroll != nullptr) ItemContainer_SCroll->SetChildCount(m_EquipmentItemRecipeArray.Num());
	if (ConsumeMaterials_SCroll != nullptr) ConsumeMaterials_SCroll->SetChildCount(m_ConsumeMaterialArray.Num());
}

void UForgingEquipmentItemPage::OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container)
{

}

void UForgingEquipmentItemPage::OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container)
{
	if (0 == rec_key) return;
	if (nullptr == Container) return;
	setCurrentForgingItem(Container->GetInventoryEquipment()->GetGameItemInfo());
}

void UForgingEquipmentItemPage::UpdateChildEquipmentItem(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryEquipContainerWidget* InventoryContainer = Cast<UInventoryEquipContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_EquipmentItemRecipeArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemEquipmentInfo info = m_EquipmentItemRecipeArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	InventoryContainer->SetButtonEventEx(this);
}

void UForgingEquipmentItemPage::UpdateChildConsumeMaterials(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_ConsumeMaterialArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_ConsumeMaterialArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	InventoryContainer->SetTextCountPerNumber(info.m_ItemCount);
}

void UForgingEquipmentItemPage::setCurrentForgingItem(FGameItemEquipmentInfo info)
{
	if (info.m_ItemRecKey == 0)
	{
		EmptyCurrentForgingItemUI();
		return;
	}
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(info.m_ItemRecKey)));

	if (nullptr == record)
	{
		EmptyCurrentForgingItemUI();
		return;
	}

	textName->SetText(FText::FromString(record->DesName));
	textCreateCountItem->SetText(FText::AsNumber(1));
	sliderCountItem->SetValue(1);
	progressbarCountItem->SetPercent(sliderCountItem->GetValue() * 1.f / sliderCountItem->MaxValue);
	textPrice->SetText(FText::AsNumber(record->NeedGold));

	// set materials
	m_ConsumeMaterialArray.Empty();
	for(int matIndex = 0; matIndex < record->Materials.Num(); ++matIndex)
	{
		m_ConsumeMaterialArray.Emplace(FGameItemInfo(record->MatCounts[matIndex], record->Materials[matIndex]));
	}
	if (nullptr != ConsumeMaterials_SCroll) ConsumeMaterials_SCroll->SetChildCount(m_ConsumeMaterialArray.Num());

	// set previous item
	m_PreviousItem->EquipItemToSlot(FGameItemEquipmentInfo(record->PreviousItem));
}

void UForgingEquipmentItemPage::EmptyCurrentForgingItemUI()
{
	textName->SetVisibility(ESlateVisibility::Hidden);
	m_currentForgingItem->EmptyUI();
	textCreateCountItem->SetText(FText::AsNumber(0));
	sliderCountItem->SetValue(0);
	progressbarCountItem->SetPercent(sliderCountItem->GetValue() * 1.f / sliderCountItem->MaxValue);
	textPrice->SetText(FText::AsNumber(0));
	m_ConsumeMaterialArray.Empty();
	if (nullptr != ConsumeMaterials_SCroll) ConsumeMaterials_SCroll->SetChildCount(m_ConsumeMaterialArray.Num());
	m_currentForgingItem->EmptyUI();
}
