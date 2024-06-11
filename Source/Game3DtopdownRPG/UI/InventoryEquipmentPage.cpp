// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryEquipmentPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryEquipContainerWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/EquipmentSlotWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "Game3DtopdownRPG/UI/MsgBox/MsgBoxReward.h"

void UInventoryEquipmentPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	for (int tabIndex = 0; tabIndex < static_cast<int32>(EEquipItemTabCategory::Max); ++tabIndex)
	{
		UButton* button = GetOwnUI<UButton>(FString::Printf(TEXT("Button_Tab_%d"), tabIndex));
		UImage* imageforcus = GetOwnUI<UImage>(FString::Printf(TEXT("Image_forcus_%d"), tabIndex));

		if (nullptr != button) TabButtons.Emplace(button);
		if (nullptr != imageforcus) TabForcuss.Emplace(imageforcus);
	}

	ScrollWidget_EquipmentItem = GetOwnUI<UScrollWidget>(TEXT("ScrollWidge_EquipmentContainer"));
	if (nullptr != ScrollWidget_EquipmentItem)
	{
		ScrollWidget_EquipmentItem->InitUnit(GameMode);
		ScrollWidget_EquipmentItem->ChildUpdateEvent.BindUObject(this, &UInventoryEquipmentPage::UpdateChildEquipmentContainer);
	}

	currentEquipSlot = GetOwnUI<UEquipmentSlotWidget>(TEXT("CurrentEquipmentSlotWidget"));
	if (nullptr != currentEquipSlot)
	{
		currentEquipSlot->InitUnit(GameMode);
		currentEquipSlot->SetDropEventEx(this);
	}

	textGrade = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesGradeItem"));
	textName = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesNameItem"));
	textDecription = GetOwnUI<UTextBlock>(TEXT("RichTextBlock_DesDescriptionItem"));
	textPrice = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesPriceItem"));
	buttonSell = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Sell"));
	if (nullptr != buttonSell) buttonSell->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapButtonSell")));

	// text Param
	for (int indexParam = 0; indexParam < 5; ++indexParam)
	{
		UOverlay* overlayParam = GetOwnUI<UOverlay>(FString::Printf(TEXT("Overlay_Stat_%d"), indexParam));
		UTextBlock* textCurrentParam = GetOwnUI<UTextBlock>(FString::Printf(TEXT("TextBlock_Param_%d"), indexParam));
		UTextBlock* textAddParam = GetOwnUI<UTextBlock>(FString::Printf(TEXT("TextBlock_ParamAdd_%d"), indexParam));
		if (nullptr != overlayParam && nullptr != textCurrentParam && nullptr != textAddParam)
		{
			statInfos.Emplace(overlayParam);
			statParamCurrent.Emplace(textCurrentParam);
			statParamAdd.Emplace(textAddParam);
		}
	}

	SetTab(EEquipItemTabCategory::All);
}

void UInventoryEquipmentPage::Update()
{
	Super::Update();

	m_currentEquipItemArray.Empty();
	switch (m_currenttab)
	{
	case EEquipItemTabCategory::All:
		m_currentEquipItemArray = GetMgr(UItemMgr)->GetItemEquipmentInInventoryArray();
		break;
	case EEquipItemTabCategory::Weapon:
		m_currentEquipItemArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Weapon, EInventoryLocation::InInventory);
		break;
	case EEquipItemTabCategory::Shield:
		m_currentEquipItemArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Shield, EInventoryLocation::InInventory);
		break;
	case EEquipItemTabCategory::Shoe:
		m_currentEquipItemArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Shoe, EInventoryLocation::InInventory);
		break;
	case EEquipItemTabCategory::Belt:
		m_currentEquipItemArray = GetMgr(UItemMgr)->GetItemEquipmentArrayByEquipPosition(EItemEquipPosition::Belt, EInventoryLocation::InInventory);
		break;
	case EEquipItemTabCategory::Max:
		break;
	default:
		break;
	}

	if (nullptr != ScrollWidget_EquipmentItem) ScrollWidget_EquipmentItem->SetChildCount(m_currentEquipItemArray.Num());
	
	if (m_currentItemEquipInfo.m_ItemRecKey != 0 && GetMgr(UItemMgr)->isHaveEquipmentItem(m_currentItemEquipInfo) == false)
	{
		SetCurrentEquipItem(FGameItemEquipmentInfo());
	}
}

void UInventoryEquipmentPage::UpdateChildEquipmentContainer(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryEquipContainerWidget* InventoryContainer = Cast<UInventoryEquipContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_currentEquipItemArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemEquipmentInfo info = m_currentEquipItemArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	InventoryContainer->SetButtonEventEx(this);

	InventoryContainer->SetCtrlButtonEventEx(this);
}

void UInventoryEquipmentPage::SetTab(EEquipItemTabCategory tab)
{
	if (EEquipItemTabCategory::Max == tab) return;
	m_currenttab = tab;

	// hide all tab forcus
	for (int indextab = 0; indextab < TabForcuss.Num(); ++indextab)
	{
		TabForcuss[indextab]->SetVisibility(ESlateVisibility::Hidden);
	}
	// show current tab
	TabForcuss[static_cast<int32>(tab)]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Update();
}

void UInventoryEquipmentPage::SetCurrentEquipItem(FGameItemEquipmentInfo info)
{
	m_currentItemEquipInfo = info;
	if (info.m_ItemRecKey == 0)
	{
		currentEquipSlot->EmptyUI();
	}
	else currentEquipSlot->EquipItemToSlot(info);
	UpdateDescriptionEquipItem();
}

void UInventoryEquipmentPage::UpdateDescriptionEquipItem()
{
	FItemEquipmentInfoRecord* infoRecord = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(m_currentItemEquipInfo.m_ItemRecKey)));
	if (nullptr != infoRecord)
	{
		textGrade->SetText(FText::FromString(GetMgr(UItemMgr)->GetItemGradeText(infoRecord->EquipmentGrape)));
		textName->SetText(FText::FromString(infoRecord->DesName));
		textPrice->SetText(FText::AsNumber(infoRecord->SellGold));
	}
	else
	{
		textGrade->SetText(FText::FromString(TEXT("")));
		textName->SetText(FText::FromString(TEXT("")));
		textPrice->SetText(FText::FromString(TEXT("0")));
	}

	// update ITem Param
	// set current item param

	if (infoRecord != nullptr)
	{
		FItemParamLevRecord* paramRecord = GetMgr(UItemMgr)->GetItemParamLevRecord(FName(FString::FromInt(infoRecord->ItemParamLevID)));

		for (int indexParam = 0; indexParam < 5; ++indexParam)
		{
			float paramvalue = 0;
			float paramvalueAdd = 0;
			switch ((ECharacterParam)indexParam)
			{
			case ECharacterParam::PhysicDamage:
				paramvalue = infoRecord->ItemEquipParam.PhysicDamage + paramRecord->ParamUpgrade.PhysicDamage * m_currentItemEquipInfo.m_ItemUgrapeLevel;
				break;
			case ECharacterParam::MagicDamage:
				paramvalue = infoRecord->ItemEquipParam.MagicDamage + paramRecord->ParamUpgrade.MagicDamage * m_currentItemEquipInfo.m_ItemUgrapeLevel;
				break;
			case ECharacterParam::HP:
				paramvalue = infoRecord->ItemEquipParam.HP + paramRecord->ParamUpgrade.HP * m_currentItemEquipInfo.m_ItemUgrapeLevel;
				break;
			case ECharacterParam::Def:
				paramvalue = infoRecord->ItemEquipParam.Def + paramRecord->ParamUpgrade.Def * m_currentItemEquipInfo.m_ItemUgrapeLevel;
				break;
			case ECharacterParam::MagicDef:
				paramvalue = infoRecord->ItemEquipParam.MagicDef + paramRecord->ParamUpgrade.MagicDef * m_currentItemEquipInfo.m_ItemUgrapeLevel;
				break;
			default:
				break;
			}

			if (0 == paramvalue && 0 == paramvalueAdd)
			{
				statInfos[indexParam]->SetVisibility(ESlateVisibility::Collapsed);
				continue;
			}

			statParamCurrent[indexParam]->SetText(FText::FromString(FString::Printf(TEXT("+%.0f"), paramvalue)));

			if (0 == paramvalueAdd)
				statParamAdd[indexParam]->SetVisibility(ESlateVisibility::Hidden);
			else
			{
				statParamAdd[indexParam]->SetText(FText::FromString(FString::Printf(TEXT("+%.0f"), paramvalueAdd)));
				statParamAdd[indexParam]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			statInfos[indexParam]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
	else
	{
		for (int indexParam = 0; indexParam < 5; ++indexParam)
		{
			statInfos[indexParam]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UInventoryEquipmentPage::OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* container)
{
	if (rec_key == 0) return;
	if (nullptr == container) return;

	SetCurrentEquipItem(container->GetGameItemInfo());
}

void UInventoryEquipmentPage::OnCtrlTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* container)
{
	FItemEquipmentInfoRecord* infoRecord = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(container->GetGameItemInfo().m_ItemRecKey)));
	if (infoRecord == nullptr) return;
	UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, FString::Printf(TEXT("Change %s to backpack success"), *infoRecord->DesName));
	GetMgr(UItemMgr)->ChangeItemEquipmentInventoryLocation(container->GetGameItemInfo(), EInventoryLocation::InBackpack);

	Update();
}

void UInventoryEquipmentPage::OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* container)
{
	if (rec_key == 0) return;
	if (nullptr == container) return;

	SetCurrentEquipItem(container->GetInventoryEquipment()->GetGameItemInfo());
}

void UInventoryEquipmentPage::OnTapButtonSell()
{
	if (m_currentItemEquipInfo.m_ItemRecKey == 0) return;

	FItemEquipmentInfoRecord* infoRecord = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(m_currentItemEquipInfo.m_ItemRecKey)));

	UUIBaseMsgBox* msg = UIMgr->OpenMsgBox(EUIMsgBoxType::Reward, FString(TEXT("Forging new equipment item success")));
	if (Cast<UMsgBoxReward>(msg))
	{
		TArray<FGameItemInfo> arrays;
		arrays.Emplace(FGameItemInfo(infoRecord->SellGold, 1001));
		Cast<UMsgBoxReward>(msg)->SetInfo(arrays);
	}

	// xu ly data
	GetMgr(UItemMgr)->RemoveItemEquipment(m_currentItemEquipInfo);

	Update();
}

void UInventoryEquipmentPage::OnTapClose()
{
	if (UIMgr != nullptr)
		UIMgr->CloseScene();
}
