// Fill out your copyright notice in the Description page of Project Settings.


#include "InternalWidget.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"

void UInternalWidget::CacheOwnUI()
{
	Super::CacheOwnUI();

	for (int menuIndex = 0; menuIndex < static_cast<int32>(EBuildingType::Max); ++menuIndex)
	{
		UHorizontalBox* menu = GetOwnUI<UHorizontalBox>(FString::Printf(TEXT("Menu_%d"), menuIndex));
		if (nullptr != menu)
		{
			ListMenu.Emplace(menu);
		}
	}

	textNameBuilding = GetOwnUI<UTextBlock>(TEXT("TextBlock_Namebuilding"));
}

void UInternalWidget::SetCurrentBuilding(EBuildingType type)
{
	// hide all menu
	for (int menuIndex = 0; menuIndex < ListMenu.Num(); ++menuIndex)
		ListMenu[menuIndex]->SetVisibility(ESlateVisibility::Collapsed);

	// show current menu
	if (ListMenu.IsValidIndex(static_cast<int32>(type)))
		ListMenu[static_cast<int32>(type)]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	switch (type)
	{
	case EBuildingType::Inventory:
		textNameBuilding->SetText(FText::FromString("Inventory Building"));
		break;
	case EBuildingType::ForgingItem:
		textNameBuilding->SetText(FText::FromString("Forging Building"));
		break;
	case EBuildingType::MakingPotion:
		textNameBuilding->SetText(FText::FromString("Making Potion Building"));
		break;
	case EBuildingType::RuneBuff:
		textNameBuilding->SetText(FText::FromString("Rune Buff Building"));
		break;
	case EBuildingType::BattleField:
		textNameBuilding->SetText(FText::FromString("Battle Stage"));
		break;
	case EBuildingType::Max:
		textNameBuilding->SetText(FText::FromString(""));
		break;
	default:
		break;
	}
	
	m_CurrentBuilding = type;
}

void UInternalWidget::OnTapBtnMenu(int Index)
{
	switch (m_CurrentBuilding)
	{
	case EBuildingType::Inventory:
		if (0 == Index)
		{
			UIMgr->OpenScene(EUIName::InventoryPage);
		}
		else if (1 == Index)
		{

		}
		break;
	case EBuildingType::ForgingItem:
		if (0 == Index)
		{
			UIMgr->OpenScene(EUIName::UpgradeItemEquipmentPage);
		}
		else if (1 == Index)
		{
			UIMgr->OpenScene(EUIName::ForgingItemEquipmentPage);
		}
		break;
	case EBuildingType::MakingPotion:
		if (0 == Index)
		{
			UIMgr->OpenScene(EUIName::MakingPotionPage);
		}
		break;
	case EBuildingType::RuneBuff:
		if (0 == Index)
		{
			UIMgr->OpenScene(EUIName::RuneBuffPage);
		}
		break;
	case EBuildingType::BattleField:
		if (0 == Index)
		{
			UIMgr->OpenScene(EUIName::BattleStagePage);
		}
		break;
	case EBuildingType::Max:
		break;
	default:
		break;
	}
}

void UInternalWidget::OnTapClose()
{
	if (UIMgr != nullptr)
		UIMgr->CloseScene();
}
