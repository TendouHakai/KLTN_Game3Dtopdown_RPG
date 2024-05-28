// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeItemEquipmentPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryEquipContainerWidget.h"
#include "Game3DtopdownRPG/UI//UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/EquipmentSlotWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"

void UUpgradeItemEquipmentPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	scrollEquipmentItem = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerItem"));
	if (nullptr != scrollEquipmentItem)
	{
		scrollEquipmentItem->InitUnit(GameMode);
		scrollEquipmentItem->ChildUpdateEvent.BindUObject(this, &UUpgradeItemEquipmentPage::UpdateChildEquipmentItem);
	}

	scrollMaterial = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerMaterial"));
	if (nullptr != scrollMaterial)
	{
		scrollMaterial->InitUnit(GameMode);
		scrollMaterial->ChildUpdateEvent.BindUObject(this, &UUpgradeItemEquipmentPage::UpdateChildMaterial);
	}

	scrollConsumeMaterial = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ConsumeMaterials"));
	if (nullptr != scrollMaterial)
	{
		scrollConsumeMaterial->InitUnit(GameMode);
		scrollConsumeMaterial->ChildUpdateEvent.BindUObject(this, &UUpgradeItemEquipmentPage::UpdateChildConsumeMaterial);
	}

	for (int tabindex = 0; tabindex < static_cast<int32>(EUgradeTabCategory::Max); ++tabindex)
	{
		UButton* button = GetOwnUI<UButton>(FString::Printf(TEXT("Button_Tab_%d"), tabindex));
		UImage* imageforcus = GetOwnUI<UImage>(FString::Printf(TEXT("Image_forcus_%d"), tabindex));

		if (nullptr != button) TabButtons.Emplace(button);
		if (nullptr != imageforcus) TabForcuss.Emplace(imageforcus);
	}

	m_CurrentEquipmentUpgradeItem = GetOwnUI<UEquipmentSlotWidget>(TEXT("UpgradeEquipmentSlotWidget"));
	if (nullptr != m_CurrentEquipmentUpgradeItem)
	{
		m_CurrentEquipmentUpgradeItem->InitUnit(GameMode);
		m_CurrentEquipmentUpgradeItem->SetDropEventEx(this);
	}

	// Description
	textGrade = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesGradeItem"));
	textNameItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesNameItem"));
	textCurrentLevel = GetOwnUI<UTextBlock>(TEXT("TextBlock_CurrentLevel"));
	textLevelAdd = GetOwnUI<UTextBlock>(TEXT("TextBlock_LevelAdd"));
	textExpAdd = GetOwnUI<UTextBlock>(TEXT("TextBlock_ExpAdd"));
	textCurrentExp = GetOwnUI<UTextBlock>(TEXT("TextBlock_CurrentExp"));
	progressBarExp = GetOwnUI<UProgressBar>(TEXT("ProgressBarExp"));

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

	OnTapTabcategory(EUgradeTabCategory::EquipmentItem);
	Update();
}

void UUpgradeItemEquipmentPage::Update()
{
	Super::Update();

	m_ItemEquipmentArray.Empty();
	m_ItemUpgradeMaterialArray.Empty();
	m_ConsumeMaterialArray.Empty();

	m_ItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentArray();
	if (nullptr != scrollEquipmentItem) scrollEquipmentItem->SetChildCount(m_ItemEquipmentArray.Num());

	m_ItemUpgradeMaterialArray = GetMgr(UItemMgr)->GetItemArrayByItemType(EItemType::UpgradeEquipmentItem);
	if (nullptr != scrollMaterial) scrollMaterial->SetChildCount(m_ItemUpgradeMaterialArray.Num());
}

void UUpgradeItemEquipmentPage::OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container)
{

}

void UUpgradeItemEquipmentPage::OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container)
{
	if (nullptr == Container) return;

	bool isExist = false;

	for (int index = 0; index < m_ConsumeMaterialArray.Num(); ++index)
	{
		if (m_ConsumeMaterialArray[index].m_ItemRecKey == rec_key)
		{
			if (Container->GetGameItemInfo().m_ItemCount <= m_ConsumeMaterialArray[index].m_ItemCount)
				m_ConsumeMaterialArray[index].m_ItemCount = Container->GetGameItemInfo().m_ItemCount;
			else m_ConsumeMaterialArray[index].m_ItemCount += 1;
			isExist = true;

			Container->SetUseCount(m_ConsumeMaterialArray[index].m_ItemCount);
		}
	}

	if (isExist == false)
	{
		FGameItemInfo info;
		info.m_ItemRecKey = rec_key;
		info.m_ItemCount = 1;

		m_ConsumeMaterialArray.Emplace(info);
		Container->SetUseCount(1);
	}

	setIncreaseUpgradeExp();

	if (nullptr != scrollConsumeMaterial) scrollConsumeMaterial->SetChildCount(m_ConsumeMaterialArray.Num());
}

void UUpgradeItemEquipmentPage::OnTapUseSubtractContainer(int32 rec_key, UInventoryContainerWidget* Container)
{
	if (nullptr == Container) return;

	int indexRemove = -1;

	for (int index = 0; index < m_ConsumeMaterialArray.Num(); ++index)
	{
		if (m_ConsumeMaterialArray[index].m_ItemRecKey == rec_key)
		{
			if (m_ConsumeMaterialArray[index].m_ItemCount <= 1)
				indexRemove = index;
			m_ConsumeMaterialArray[index].m_ItemCount -= 1;

			Container->SetUseCount(m_ConsumeMaterialArray[index].m_ItemCount);
		}
	}

	if(m_ConsumeMaterialArray.IsValidIndex(indexRemove))
		m_ConsumeMaterialArray.RemoveAt(indexRemove);

	setIncreaseUpgradeExp();
	
	if (nullptr != scrollConsumeMaterial) scrollConsumeMaterial->SetChildCount(m_ConsumeMaterialArray.Num());
}

void UUpgradeItemEquipmentPage::OnDropEquipContainer(int32 rec_key, UEquipmentSlotWidget* Container)
{
	if (nullptr == Container) return;
	SetCurrentUpgradeEquipItem(Container->GetInventoryEquipment()->GetGameItemInfo());
}

void UUpgradeItemEquipmentPage::OnTapTabcategory(EUgradeTabCategory category)
{
	// hide all tab forcus
	for (int indextab = 0; indextab < TabForcuss.Num(); ++indextab)
	{
		TabForcuss[indextab]->SetVisibility(ESlateVisibility::Hidden);
	}
	// show current tab
	TabForcuss[static_cast<int32>(category)]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_CurrentCategory = category;

	switch (m_CurrentCategory)
	{
	case EUgradeTabCategory::EquipmentItem:
		scrollEquipmentItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		scrollMaterial->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EUgradeTabCategory::UpgradeMaterial:
		scrollEquipmentItem->SetVisibility(ESlateVisibility::Collapsed);
		scrollMaterial->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case EUgradeTabCategory::Max:
		break;
	default:
		break;
	}
}

void UUpgradeItemEquipmentPage::OnTapLevelUpBtn(EUgradeTabCategory category)
{

}

void UUpgradeItemEquipmentPage::UpdateChildMaterial(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_ItemUpgradeMaterialArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_ItemUpgradeMaterialArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	//InventoryContainer->OwnerDelegateEx.Unbind();
	InventoryContainer->SetButtonEventEx(this);
	InventoryContainer->SetButtonUseSubtractEventEx(this);
}

void UUpgradeItemEquipmentPage::UpdateChildEquipmentItem(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryEquipContainerWidget* InventoryContainer = Cast<UInventoryEquipContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_ItemEquipmentArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemEquipmentInfo info = m_ItemEquipmentArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	//InventoryContainer->OwnerDelegateEx.Unbind();
	InventoryContainer->SetButtonEventEx(this);
}

void UUpgradeItemEquipmentPage::UpdateChildConsumeMaterial(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_ConsumeMaterialArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_ConsumeMaterialArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	//InventoryContainer->OwnerDelegateEx.Unbind();
	//InventoryContainer->SetButtonEventEx(this);
}

void UUpgradeItemEquipmentPage::SetCurrentUpgradeEquipItem(FGameItemEquipmentInfo info)
{
	if (info.m_ItemRecKey == 0) return;
	m_CurrentGameItemInfo = info;
	UpdateDescriptionEquipItem();
}

void UUpgradeItemEquipmentPage::UpdateDescriptionEquipItem()
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(m_CurrentGameItemInfo.m_ItemRecKey)));
	textGrade->SetText(FText::FromString(GetMgr(UItemMgr)->GetItemGradeText(record->EquipmentGrape)));
	textNameItem->SetText(FText::FromString(record->DesName));
	//textLevelAdd->SetVisibility(ESlateVisibility::Hidden);
	//textExpAdd->SetVisibility(ESlateVisibility::Hidden);
	//textCurrentExp->SetVisibility(ESlateVisibility::Hidden);

	setIncreaseUpgradeExp();

	for (int indexParam = 0; indexParam < 5; ++indexParam)
	{
		float paramvalue = 0;
		switch ((ECharacterParam)indexParam)
		{
		case ECharacterParam::PhysicDamage:
			paramvalue = record->ItemEquipParam.PhysicDamage;
			break;
		case ECharacterParam::MagicDamage:
			paramvalue = record->ItemEquipParam.MagicDamage;
			break;
		case ECharacterParam::HP:
			paramvalue = record->ItemEquipParam.HP;
			break;
		case ECharacterParam::Def:
			paramvalue = record->ItemEquipParam.Def;
			break;
		case ECharacterParam::MagicDef:
			paramvalue = record->ItemEquipParam.MagicDef;
			break;
		default:
			break;
		}

		if (0 == paramvalue)
		{
			statInfos[indexParam]->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}
		statParamCurrent[indexParam]->SetText(FText::FromString(FString::Printf(TEXT("+%.0f"), paramvalue)));
		statParamAdd[indexParam]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUpgradeItemEquipmentPage::setIncreaseUpgradeExp()
{
	int32 UpgradeExp = 0;
	for (int index = 0; index < m_ConsumeMaterialArray.Num(); ++index)
	{
		FUpgradeLevelOfMaterialRecord* UpgradeRecord = GetMgr(UItemMgr)->GetUpgradeLevelOfMaterialRecord(FName(FString::FromInt(m_ConsumeMaterialArray[index].m_ItemRecKey)));
		UpgradeExp += (UpgradeRecord->expUpgrade * m_ConsumeMaterialArray[index].m_ItemCount);
	}

	// set current level
	textCurrentLevel->SetText(FText::FromString(FString::Printf(TEXT("Lev %d"), m_CurrentGameItemInfo.m_ItemUgrapeLevel)));

	// set increase level
	int TotalExp = m_CurrentGameItemInfo.m_ItemUgrapeExp + UpgradeExp;
	FItemEquipmentLevRecord* record = GetMgr(UItemMgr)->GetItemEquipmentLevelRecordByTotalExp(TotalExp);
	int IncreaseLevel = record->Level - m_CurrentGameItemInfo.m_ItemUgrapeLevel;
	
	if (UpgradeExp == 0)
		textExpAdd->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		textExpAdd->SetText(FText::FromString(FString::Printf(TEXT("+%d exp"), UpgradeExp)));
		textExpAdd->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (IncreaseLevel == 0)
		textLevelAdd->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		textLevelAdd->SetText(FText::FromString(FString::Printf(TEXT("+%d"), IncreaseLevel)));
		textLevelAdd->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
