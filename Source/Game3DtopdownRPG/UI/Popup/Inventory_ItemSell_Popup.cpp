// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory_ItemSell_Popup.h"
#include "../UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "../UIUnit/UIBaseButton.h"
#include "Game3DtopdownRPG/UI/MsgBox/MsgBoxReward.h"

void UInventory_ItemSell_Popup::CacheOwnUI()
{
	Super::CacheOwnUI();

	InventoryContainer = GetOwnUI<UInventoryContainerWidget>(TEXT("InventoryContainerWidget"));
	textNameItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_NameItem"));
	textCountItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_QuanityItem"));
	textSellCountItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_SellQuanity"));
	textSellPriceItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_TotalSellPrice"));
	sliderCountItem = GetOwnUI<USlider>(TEXT("Slider_CountItem"));
	progressbarCountItem = GetOwnUI<UProgressBar>(TEXT("ProgressBar_CountItem"));
	SellButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Sell"));
	if (nullptr != SellButton)
	{
		SellButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapSellButton")));
	}
	CancelButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Cancel"));
	if (nullptr != CancelButton)
	{
		CancelButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapCancelButton")));
	}
}

void UInventory_ItemSell_Popup::SetInfo(FGameItemInfo iteminfo)
{
	GameItemInfo = iteminfo;

	if (nullptr == InventoryContainer) return;
	InventoryContainer->SetInfo(GameItemInfo);

	if (nullptr == textNameItem || nullptr == textNameItem || nullptr == textSellCountItem || nullptr == textSellPriceItem)
		return;

	FItemInfoRecord* ItemInfoRecord = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(GameItemInfo.m_ItemRecKey)));
	if (nullptr == ItemInfoRecord) return;

	textCountItem->SetText(FText::AsNumber(GameItemInfo.m_ItemCount));
	textNameItem->SetText(FText::FromString(ItemInfoRecord->DesName));
	textSellCountItem->SetText(FText::AsNumber(sellcount));
	textSellPriceItem->SetText(FText::AsNumber(sellPrice));

	sliderCountItem->SetMaxValue(GameItemInfo.m_ItemCount);

	SetSellItemCount(1);
}

void UInventory_ItemSell_Popup::OnValueChangedSliderCountItem(int32 Value)
{
	SetSellItemCount(Value);
}

void UInventory_ItemSell_Popup::OnTapAddSellItemButton()
{
	if (sellcount >= GameItemInfo.m_ItemCount) return;
	sliderCountItem->SetValue(++sellcount);
}

void UInventory_ItemSell_Popup::OnTapSubtractSellItemButton()
{
	if (sellcount <= 1) return;
	sliderCountItem->SetValue(--sellcount);
}

void UInventory_ItemSell_Popup::OnTapMinSellItemButton()
{
	sliderCountItem->SetValue(1);
}

void UInventory_ItemSell_Popup::OnTapMaxSellItemButton()
{
	sliderCountItem->SetValue(GameItemInfo.m_ItemCount);
}

void UInventory_ItemSell_Popup::OnTapCancelButton()
{
	UIMgr->CloseUI(this);
}

void UInventory_ItemSell_Popup::OnTapSellButton()
{
	if (GameItemInfo.m_ItemRecKey == 0) return;

	GetMgr(UItemMgr)->RemoveItem(GameItemInfo.m_ItemRecKey, sellcount, GameItemInfo.m_InventoryLocation);
	GetMgr(UItemMgr)->AddGold(sellPrice);
	
	UUIBaseMsgBox* msg = UIMgr->OpenMsgBox(EUIMsgBoxType::Reward, FString(TEXT("Decay equipmment")));
	if (Cast<UMsgBoxReward>(msg))
	{
		TArray<FGameItemInfo> arrays;
		arrays.Emplace(FGameItemInfo(sellcount, 1001));
		Cast<UMsgBoxReward>(msg)->SetInfo(arrays);
	}

	HandleSell.ExecuteIfBound();

	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}

void UInventory_ItemSell_Popup::SetSellItemCount(int32 count)
{
	if (count < 0 || count > GameItemInfo.m_ItemCount)
		return;

	FItemInfoRecord* ItemInfoRecord = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(GameItemInfo.m_ItemRecKey)));
	if (nullptr == ItemInfoRecord) return;

	sellcount = count;
	sellPrice = sellcount * ItemInfoRecord->SellGold;

	// update UI
	textSellCountItem->SetText(FText::AsNumber(sellcount));
	textSellPriceItem->SetText(FText::AsNumber(sellPrice));

	sliderCountItem->SetValue(sellcount);
	progressbarCountItem->SetPercent(sellcount * 1.f / GameItemInfo.m_ItemCount);
}
