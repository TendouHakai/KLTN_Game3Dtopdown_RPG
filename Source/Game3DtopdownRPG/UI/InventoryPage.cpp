// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPage.h"
#include "UIUnit/ScrollWidget.h"
#include "UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"

#include "UIUnit/UIBaseButton.h"
#include "Popup/Inventory_ItemSell_Popup.h"

void UInventoryPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	ItemContainer_SCroll = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerItem"));
	if (nullptr != ItemContainer_SCroll)
	{
		ItemContainer_SCroll->InitUnit(GameMode);
		ItemContainer_SCroll->ChildUpdateEvent.BindUObject(this, &UInventoryPage::UpdateChildItem);
	}

	TabImagesForcus.Empty();
	for (int indexTab = 0; indexTab < static_cast<int32>(EItemCategory::Max); ++indexTab)
	{
		UImage* imageTabforcus = GetOwnUI<UImage>(FString::Printf(TEXT("TabForcus_%d"), indexTab + 1));
		if (nullptr != imageTabforcus)
		{
			TabImagesForcus.Emplace(imageTabforcus);
		}
	}

	ItemContainer = GetOwnUI<UInventoryContainerWidget>(TEXT("InventoryContainerWidget_Des"));
	if (nullptr == ItemContainer) ItemContainer->IsInteract = false;
	textGradeItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesGradeItem"));
	textNameItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesNameItem"));
	textDecriptionItem = GetOwnUI<URichTextBlock>(TEXT("RichTextBlock_DesDescriptionItem"));
	textPriceItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesPriceItem"));

	SellButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Sell"));
	if (nullptr != SellButton) SellButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapSellItem")));
	UseButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Use"));
	if (nullptr != UseButton) UseButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapUseItem")));

	vertical_DesItem = GetOwnUI<UVerticalBox>(TEXT("VerticalBox_DescriptionItem"));

	Update();
}

void UInventoryPage::Update()
{
	Super::Update();
	m_CurrentItemArray.Empty();
	setCurrentSelectedItem(nullptr);

	for (FGameItemInfo iteminfo : GetMgr(UItemMgr)->GetItemArray())
	{
		if (IsItemInCategory(GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)))->Category))
		{
			m_CurrentItemArray.Emplace(iteminfo);
		}
	}

	if (nullptr != ItemContainer_SCroll) ItemContainer_SCroll->SetChildCount(m_CurrentItemArray.Num());
}

void UInventoryPage::OnTapTabcategory(EItemCategory category)
{
	// hide all tab forcus
	for (int indextab = 0; indextab < TabImagesForcus.Num(); ++indextab)
	{
		TabImagesForcus[indextab]->SetVisibility(ESlateVisibility::Hidden);
	}
	// show current tab
	TabImagesForcus[static_cast<int32>(category)]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_CurItemType = category;

	// update item list
	Update();
}

void UInventoryPage::OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container)
{
	if (nullptr == Container) return;
	
	setCurrentSelectedItem(Container);
}

void UInventoryPage::OnTapSellItem()
{
	UInventory_ItemSell_Popup* SellPopup = Cast<UInventory_ItemSell_Popup>(UIMgr->OpenUI(EUIName::InventoryItemSellPopup));
	if (nullptr != SellPopup)
		SellPopup->SetInfo(CurrentSelectedItem->GetGameItemInfo());
}

void UInventoryPage::OnTapUseItem()
{
	if (nullptr == CurrentSelectedItem) return;
	FGameItemInfo gameinfo = CurrentSelectedItem->GetGameItemInfo();
	FItemInfoRecord* iteminfo = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(gameinfo.m_ItemRecKey)));
	if (nullptr == iteminfo)
		return;

	if (iteminfo->ItemType == EItemType::Max)
	{
		UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, FString(TEXT("test message Box")));
	}
}

void UInventoryPage::UpdateChildItem(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_CurrentItemArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_CurrentItemArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	//InventoryContainer->OwnerDelegateEx.Unbind();
	InventoryContainer->SetButtonEventEx(this);
}

bool UInventoryPage::IsItemInCategory(EItemCategory category)
{
	if (m_CurItemType == category || m_CurItemType == EItemCategory::All)
		return true;
	return false;
}

void UInventoryPage::UpdateDecriptionItem()
{
	if (nullptr == CurrentSelectedItem)
	{
		if (nullptr == vertical_DesItem) return;
		vertical_DesItem->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	if (nullptr == vertical_DesItem) return;
	vertical_DesItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	ItemContainer->SetInfo(CurrentSelectedItem);

	FGameItemInfo gameinfo = CurrentSelectedItem->GetGameItemInfo();

	FItemInfoRecord* iteminfo = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(gameinfo.m_ItemRecKey)));
	if (nullptr == iteminfo) return;
	
	if (nullptr == textGradeItem || nullptr == textNameItem || nullptr == textDecriptionItem || nullptr == textPriceItem) return;

	textGradeItem->SetText(FText::FromString(GetMgr(UItemMgr)->GetItemGradeText(iteminfo->ItemGrape)));
	textNameItem->SetText(FText::FromString(iteminfo->DesName));
	textDecriptionItem->SetText(FText::FromString(GetMgr(UItemMgr)->GetDescriptionItem(*iteminfo)));
	textPriceItem->SetText(FText::AsNumber(iteminfo->SellGold));
}

void UInventoryPage::setCurrentSelectedItem(UInventoryContainerWidget* selectedItem)
{
	CurrentSelectedItem = selectedItem;
	UpdateDecriptionItem();
}
