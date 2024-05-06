// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPage.h"
#include "UIUnit/ScrollWidget.h"
#include "UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"

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

	Update();
}

void UInventoryPage::Update()
{
	Super::Update();
	m_CurrentItemArray.Empty();

	for (FGameItemInfo iteminfo : GetMgr(UItemMgr)->GetItemArray())
	{
		if (IsItemInCategory(GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)))->Category))
		{
			m_CurrentItemArray.Emplace(&iteminfo);
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

void UInventoryPage::UpdateChildItem(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_CurrentItemArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo* info = m_CurrentItemArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
}

bool UInventoryPage::IsItemInCategory(EItemCategory category)
{
	if (m_CurItemType == category || m_CurItemType == EItemCategory::All)
		return true;
	return false;
}
