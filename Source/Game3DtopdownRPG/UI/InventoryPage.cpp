// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPage.h"
#include "UIUnit/ScrollWidget.h"
#include "UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffControllerComponent.h"
#include "Game3DtopdownRPG/Battle/Buff/BaseBuff.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/FlameDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/FreezeDeBuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/BleedingDeBuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/BlindnessDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/AttackDamageDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/SlowDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffList/StunDebuff.h"

#include "UIUnit/UIBaseButton.h"
#include "UIUnit/TopMenuWidget.h"
#include "Popup/Inventory_ItemSell_Popup.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

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

	TopMenu = GetOwnUI<UTopMenuWidget>(TEXT("TopMenuWidgetBP"));
	if (nullptr != TopMenu) TopMenu->InitUnit(GameMode);

	Update();
}

void UInventoryPage::Update()
{
	Super::Update();
	m_CurrentItemArray.Empty();
	setCurrentSelectedItem(nullptr);

	for (FGameItemInfo iteminfo : GetMgr(UItemMgr)->GetItemInInventoryArray())
	{
		if (IsItemInCategory(GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(iteminfo.m_ItemRecKey)))->Category))
		{
			m_CurrentItemArray.Emplace(iteminfo);
		}
	}

	if (nullptr != ItemContainer_SCroll) ItemContainer_SCroll->SetChildCount(m_CurrentItemArray.Num());

	if (nullptr != TopMenu) TopMenu->Update();
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

void UInventoryPage::OnCtrlTapInventoryContainer(int32 rec_key, UInventoryContainerWidget* Container)
{
	if (nullptr == Container) return;

	GetMgr(UItemMgr)->ChangeItemInventoryLocation(Container->GetGameItemInfo(), Container->GetGameItemInfo().m_ItemCount, EInventoryLocation::InBackpack);

	Update();
}

void UInventoryPage::OnTapSellItem()
{
	UInventory_ItemSell_Popup* SellPopup = Cast<UInventory_ItemSell_Popup>(UIMgr->OpenUI(EUIName::InventoryItemSellPopup));
	if (nullptr != SellPopup)
	{
		SellPopup->SetInfo(CurrentSelectedItem->GetGameItemInfo());
		SellPopup->HandleSell.BindUFunction(this, FName(TEXT("OnHandleSell")));
	}
}

void UInventoryPage::OnHandleSell()
{
	Update();
}

void UInventoryPage::OnTapUseItem()
{
	if (nullptr == CurrentSelectedItem) return;
	FGameItemInfo gameinfo = CurrentSelectedItem->GetGameItemInfo();
	FItemInfoRecord* iteminfo = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(gameinfo.m_ItemRecKey)));
	if (nullptr == iteminfo)
		return;

	if (iteminfo->ItemType == EItemType::Potion)
	{
		FItemBuffRecord* record = GetMgr(UItemMgr)->GetItemBufInfoRecord(FName(FString::FromInt(gameinfo.m_ItemRecKey)));
		if (record == nullptr) return;

		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter == nullptr) return;
		ABaseCharacter* character = Cast<ABaseCharacter>(PlayerCharacter);
		if (character == nullptr) return;

		if (record->IsBuff)
		{
			character->HeroBuffController->CreateBuff(character, record->buffinfo);
		}
		else
		{
			TArray<UBaseBuff*> buffs;
			switch (record->buffinfo.BuffType)
			{
			case EHeroBuffType::Flame:				character->FindHaveBuff(UFlameDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Freezing:			character->FindHaveBuff(UFreezeDeBuff::StaticClass(), buffs); break;
			case EHeroBuffType::Bleeding:			character->FindHaveBuff(UBleedingDeBuff::StaticClass(), buffs); break;
			case EHeroBuffType::Blindness:			character->FindHaveBuff(UBlindnessDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Damage_Decrease:	character->FindHaveBuff(UAttackDamageDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Slow:				character->FindHaveBuff(USlowDebuff::StaticClass(), buffs); break;
			case EHeroBuffType::Stun:				character->FindHaveBuff(UStunDebuff::StaticClass(), buffs); break;
			default:
				break;
			}

			for (UBaseBuff* buff : buffs)
			{
				buff->EndBuff();
			}
		}
		FString str = FString::Printf(TEXT("Used %s"), *iteminfo->DesName);
		UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, str);
	}

	GetMgr(UItemMgr)->RemoveItem(gameinfo.m_ItemRecKey, 1, gameinfo.m_InventoryLocation);

	Update();
}

void UInventoryPage::OnTapClose()
{
	if (UIMgr != nullptr)
		UIMgr->CloseScene();
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
	InventoryContainer->SetCtrlTapEventEx(this);
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
