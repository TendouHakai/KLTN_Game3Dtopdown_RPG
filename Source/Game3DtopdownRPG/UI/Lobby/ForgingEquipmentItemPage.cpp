// Fill out your copyright notice in the Description page of Project Settings.


#include "ForgingEquipmentItemPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/EquipmentSlotWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryEquipContainerWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/UI/MsgBox/MsgBoxReward.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"

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

	// Forging button
	ForgingBtn = GetOwnUI<UUIBaseButton>(TEXT("Button_Forging"));
	if (nullptr != ForgingBtn)
	{
		ForgingBtn->OnClicked_Delegate.Unbind();
		ForgingBtn->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapForgingItemBtn")));
	}

	Update();
}

void UForgingEquipmentItemPage::Update()
{
	Super::Update();

	m_EquipmentItemRecipeArray.Empty();

	m_EquipmentItemRecipeArray = GetMgr(UItemMgr)->GetAllItemEquipmentRecipe();
	if (ItemContainer_SCroll != nullptr) ItemContainer_SCroll->SetChildCount(m_EquipmentItemRecipeArray.Num());
	if (ConsumeMaterials_SCroll != nullptr) ConsumeMaterials_SCroll->SetChildCount(m_ConsumeMaterialArray.Num());

	if (m_PreviousItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey > 0)
	{
		m_PreviousItem->EquipItemToSlot(FGameItemEquipmentInfo(m_PreviousItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey));
		m_PreviousItem->GetInventoryEquipment()->SetTextCountPerNumber(m_Count);
	}
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

void UForgingEquipmentItemPage::OnTapAddItemButton()
{
	if (m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey == 0) return;
	if (m_Count + 1 > sliderCountItem->GetMaxValue())
		SetCountItem(sliderCountItem->GetMaxValue());
	else SetCountItem(m_Count + 1);
}

void UForgingEquipmentItemPage::OnTapSubtractItemButton()
{
	if (m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey == 0) return;
	if(m_Count - 1 <= 0)
		SetCountItem(1);
	else SetCountItem(m_Count - 1);
}

void UForgingEquipmentItemPage::OnTapMaxItemItemButton()
{
	if (m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey == 0) return;

	int32 countmax = 50;

	for (int32 matindex = 0; matindex < m_ConsumeMaterialArray.Num(); ++matindex)
	{
		FGameItemInfo info = GetMgr(UItemMgr)->FindItem(m_ConsumeMaterialArray[matindex].m_ItemRecKey);
		int32 count = info.m_ItemCount / m_ConsumeMaterialArray[matindex].m_ItemCount;
		if (countmax > count) countmax = count;
	}

	int32 countitem = GetMgr(UItemMgr)->CountItemEqupiment(m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey);
	if (countmax > countitem) countmax = countitem;

	if (countmax > sliderCountItem->GetMaxValue())
		SetCountItem(sliderCountItem->GetMaxValue());
	else if (countmax <= 0)
		SetCountItem(1);
	else
		SetCountItem(countmax);

}

void UForgingEquipmentItemPage::OnTapMinItemButton()
{
	if (m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey == 0) return;
	SetCountItem(1);
}

void UForgingEquipmentItemPage::OnValueChangeCountItemSlider(int32 count)
{
	SetCountItem(count);
}

void UForgingEquipmentItemPage::OnTapForgingItemBtn()
{
	int32 errorcode = -1;
	EResult result = GetMgr(UItemMgr)->ForgingItemEquipment(m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey, m_Count, errorcode);

	if (result == EResult::Fail)
	{
		switch ((EErrorForgingItemCode)errorcode)
		{
		case EErrorForgingItemCode::NotHaveForgingItemRecipe:
			UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, FString(TEXT("Not have forging equipment item recipe")));
			break;
		case EErrorForgingItemCode::NotEnoughMaterials:
			UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, FString(TEXT("Not enough materials")));
			break;
		case EErrorForgingItemCode::NotEnoughPreviousItem:
			UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, FString(TEXT("Not enough previous equipment item")));
			break;
		default:
			break;
		}
	}
	else if(result == EResult::Success)
	{
		UUIBaseMsgBox* msg = UIMgr->OpenMsgBox(EUIMsgBoxType::Reward, FString(TEXT("Forging new equipment item success")));
		if (Cast<UMsgBoxReward>(msg))
		{
			TArray<FGameItemEquipmentInfo> arrays;
			arrays.Emplace(FGameItemEquipmentInfo(m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey, m_Count));
			Cast<UMsgBoxReward>(msg)->SetInfo(arrays);

			SetCountItem(1);
		}
	}
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
	SetCountItem(1);
}

void UForgingEquipmentItemPage::EmptyCurrentForgingItemUI()
{
	textName->SetVisibility(ESlateVisibility::Hidden);
	m_currentForgingItem->EmptyUI();
	SetCountItem(0);
	m_ConsumeMaterialArray.Empty();
	if (nullptr != ConsumeMaterials_SCroll) ConsumeMaterials_SCroll->SetChildCount(m_ConsumeMaterialArray.Num());
	m_currentForgingItem->EmptyUI();
}

void UForgingEquipmentItemPage::SetCountItem(int32 count)
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey)));

	if (nullptr == record) return;

	if (count <= 0)
	{
		m_Count = 0;
	}
	else
	{
		m_Count = count;
		sliderCountItem->SetVisibility(ESlateVisibility::Visible);
	}

	textCreateCountItem->SetText(FText::AsNumber(m_Count));
	sliderCountItem->SetValue(m_Count);
	progressbarCountItem->SetPercent(sliderCountItem->GetValue() * 1.f / sliderCountItem->GetMaxValue());
	textPrice->SetText(FText::AsNumber(record->NeedGold* m_Count));
	UpdateMaterials(m_Count);
}

void UForgingEquipmentItemPage::UpdateMaterials(int32 count)
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(m_currentForgingItem->GetInventoryEquipment()->GetGameItemInfo().m_ItemRecKey)));
	// set materials
	m_ConsumeMaterialArray.Empty();
	if (nullptr == record)
	{
		if (nullptr != ConsumeMaterials_SCroll) ConsumeMaterials_SCroll->SetChildCount(m_ConsumeMaterialArray.Num());
		m_currentForgingItem->EmptyUI();
		return;
	}

	for (int matIndex = 0; matIndex < record->Materials.Num(); ++matIndex)
	{
		m_ConsumeMaterialArray.Emplace(FGameItemInfo(record->MatCounts[matIndex]*count, record->Materials[matIndex]));
	}
	if (nullptr != ConsumeMaterials_SCroll) ConsumeMaterials_SCroll->SetChildCount(m_ConsumeMaterialArray.Num());

	// set previous item
	m_PreviousItem->EquipItemToSlot(FGameItemEquipmentInfo(record->PreviousItem));
	m_PreviousItem->GetInventoryEquipment()->SetTextCountPerNumber(count);
}
