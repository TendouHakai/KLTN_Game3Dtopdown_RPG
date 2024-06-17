// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeItemEquipmentPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/Util/Managers/TableMgr.h"
#include "Game3DtopdownRPG/Util/Managers/HeroMgr.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryEquipContainerWidget.h"
#include "Game3DtopdownRPG/UI//UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/EquipmentSlotWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "Game3DtopdownRPG/UI/UIUnit/TopMenuWidget.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "Game3DtopdownRPG/UI/MsgBox/MsgBoxReward.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	// Button
	LevUpBtn = GetOwnUI<UUIBaseButton>(TEXT("Button_LevelUp"));
	if (nullptr != LevUpBtn)
	{
		LevUpBtn->OnClicked_Delegate.Unbind();
		LevUpBtn->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapLevelUpBtn")));
	}

	TopMenu = GetOwnUI<UTopMenuWidget>(TEXT("TopMenuWidgetBP"));
	if (nullptr != TopMenu) TopMenu->InitUnit(GameMode);
		
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

	m_ItemUpgradeMaterialArray = GetMgr(UItemMgr)->GetItemArrayByItemType(EItemType::UpgradeEquipmentItem, EInventoryLocation::All);
	if (nullptr != scrollMaterial) scrollMaterial->SetChildCount(m_ItemUpgradeMaterialArray.Num());

	if (nullptr != scrollConsumeMaterial) 
	{ 
		scrollConsumeMaterial->SetChildCount(m_ConsumeMaterialArray.Num()); 
		setIncreaseUpgradeExp();
	}

	if (m_CurrentGameItemInfo.m_ItemRecKey != 0)
	{
		if (GetMgr(UItemMgr)->isHaveEquipmentItem(m_CurrentGameItemInfo) == false)
		{
			FGameItemEquipmentInfo info;
			SetCurrentUpgradeEquipItem(info);
		}
	}

	if (nullptr != TopMenu) TopMenu->Update();
}

void UUpgradeItemEquipmentPage::OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container)
{
	if (rec_key == 0) return;
	if (nullptr == Container) return;
	SetCurrentUpgradeEquipItem(Container->GetGameItemInfo());
}

void UUpgradeItemEquipmentPage::OnCtrlTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container)
{
	if (rec_key == 0) return;
	if (nullptr == Container) return;
	
	FItemEquipmentInfoRecord* ItemEquipmentInfoRecord = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(rec_key)));
	if (nullptr == ItemEquipmentInfoRecord) return;

	FExpForGradeRecord* ExpForGradeRecord = GetMgr(UItemMgr)->GetExpForGradeRecord(FName(FString::FromInt((int32)ItemEquipmentInfoRecord->EquipmentGrape)));
	if (nullptr == ExpForGradeRecord) return;

	int64 TotalExp = ExpForGradeRecord->expDecay + Container->GetGameItemInfo().m_ItemUgrapeExp;

	TArray<FGameItemInfo> MaterialArray;
	DecayExp(TotalExp, MaterialArray);

	GetMgr(UItemMgr)->RemoveItemEquipment(Container->GetGameItemInfo());

	UUIBaseMsgBox* msg = UIMgr->OpenMsgBox(EUIMsgBoxType::Reward, FString(TEXT("Decay equipmment")));
	if (Cast<UMsgBoxReward>(msg))
	{
		Cast<UMsgBoxReward>(msg)->SetInfo(MaterialArray);
	}

	Update();
}

void UUpgradeItemEquipmentPage::OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container)
{
	if (nullptr == Container) return;
	if (IncreaseLevel + m_CurrentGameItemInfo.m_ItemUgrapeLevel >= GetMgr(UItemMgr)->GetMaxEquipmentLevelByTotalExp()) return;

	bool isExist = false;
	FGameItemInfo Iteminfo = Container->GetGameItemInfo();

	for (int index = 0; index < m_ConsumeMaterialArray.Num(); ++index)
	{
		if (m_ConsumeMaterialArray[index].m_ItemRecKey == rec_key && m_ConsumeMaterialArray[index].m_InventoryLocation == Iteminfo.m_InventoryLocation)
		{
			if (Container->GetGameItemInfo().m_ItemCount <= m_ConsumeMaterialArray[index].m_ItemCount)
				m_ConsumeMaterialArray[index].m_ItemCount = Iteminfo.m_ItemCount;
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
		info.m_InventoryLocation = Iteminfo.m_InventoryLocation;

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

void UUpgradeItemEquipmentPage::OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container)
{
	if (nullptr == Container) return;
	SetCurrentUpgradeEquipItem(Container->GetInventoryEquipment()->GetGameItemInfo());
	Container->GetInventoryEquipment()->ShowInventoryLocation(true);
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
	if (m_CurrentGameItemInfo.m_ItemRecKey == 0) return;
	if (m_ConsumeMaterialArray.Num() == 0) return;

	FGameItemEquipmentInfo newinfo = GetMgr(UItemMgr)->UpgradeLevelItemEquipment(m_CurrentGameItemInfo, m_ConsumeMaterialArray);
	if (0 == newinfo.m_ItemRecKey) return;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerCharacter != nullptr)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(PlayerCharacter);
		if (character != nullptr)
			GetMgr(UHeroMgr)->LevelUpItemEquipmentHeroParam(character, newinfo);
	}
	m_ConsumeMaterialArray.Empty();

	SetCurrentUpgradeEquipItem(newinfo);

	Update();
}

void UUpgradeItemEquipmentPage::OnTapCloseBtn()
{
	if (UIMgr != nullptr)
		UIMgr->CloseScene();
}

void UUpgradeItemEquipmentPage::UpdateChildMaterial(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_ItemUpgradeMaterialArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_ItemUpgradeMaterialArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	InventoryContainer->ShowInventoryLocation(true);

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
	InventoryContainer->ShowInventoryLocation(true);

	InventoryContainer->SetButtonEventEx(this);

	InventoryContainer->SetCtrlButtonEventEx(this);
}

void UUpgradeItemEquipmentPage::UpdateChildConsumeMaterial(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_ConsumeMaterialArray.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_ConsumeMaterialArray[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	InventoryContainer->ShowInventoryLocation(true);
	//InventoryContainer->OwnerDelegateEx.Unbind();
	//InventoryContainer->SetButtonEventEx(this);
}

void UUpgradeItemEquipmentPage::SetCurrentUpgradeEquipItem(FGameItemEquipmentInfo info)
{
	m_CurrentGameItemInfo = info;
	if (info.m_ItemRecKey == 0)
	{
		m_CurrentEquipmentUpgradeItem->EmptyUI();
	}
	else m_CurrentEquipmentUpgradeItem->EquipItemToSlot(info);
	UpdateDescriptionEquipItem();
}

void UUpgradeItemEquipmentPage::UpdateDescriptionEquipItem()
{
	FItemEquipmentInfoRecord* record = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(m_CurrentGameItemInfo.m_ItemRecKey)));
	if (nullptr != record)
	{
		textGrade->SetText(FText::FromString(GetMgr(UItemMgr)->GetItemGradeText(record->EquipmentGrape)));
		textNameItem->SetText(FText::FromString(record->DesName));
	}
	else
	{
		textGrade->SetText(FText::FromString(TEXT("")));
		textNameItem->SetText(FText::FromString(TEXT("")));
	}

	setIncreaseUpgradeExp();
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

	IncreaseLevel = 0;
	if (nullptr != record) 
		IncreaseLevel = record->Level - m_CurrentGameItemInfo.m_ItemUgrapeLevel;

	if (IncreaseLevel == 0)
		textLevelAdd->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		textLevelAdd->SetText(FText::FromString(FString::Printf(TEXT("+%d"), IncreaseLevel)));
		textLevelAdd->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	// Update Exp
	if (nullptr != record)
	{
		float currentExp = m_CurrentGameItemInfo.m_ItemUgrapeExp + UpgradeExp - record->expStart;

		if (record->Level >= GetMgr(UItemMgr)->GetMaxEquipmentLevelByTotalExp())
		{
			progressBarExp->SetPercent(1.f);
			textCurrentExp->SetText(FText::FromString("Max level"));
		}
		else
		{
			progressBarExp->SetPercent(currentExp * 1.0f / (record->expEnd - record->expStart));
			textCurrentExp->SetText(FText::FromString(FString::Printf(TEXT("%0.f/%0.f exp"), currentExp, (record->expEnd - record->expStart))));
		}
	}

	if (UpgradeExp == 0)
		textExpAdd->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		textExpAdd->SetText(FText::FromString(FString::Printf(TEXT("+%d exp"), UpgradeExp)));
		textExpAdd->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	// update ITem Param
	// set current item param
	FItemEquipmentInfoRecord* infoRecord = GetMgr(UItemMgr)->GetItemEquipmentInfoRecord(FName(FString::FromInt(m_CurrentGameItemInfo.m_ItemRecKey)));

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
				paramvalue = infoRecord->ItemEquipParam.PhysicDamage + paramRecord->ParamUpgrade.PhysicDamage * m_CurrentGameItemInfo.m_ItemUgrapeLevel;
				paramvalueAdd = paramRecord->ParamUpgrade.PhysicDamage * IncreaseLevel;
				break;
			case ECharacterParam::MagicDamage:
				paramvalue = infoRecord->ItemEquipParam.MagicDamage + paramRecord->ParamUpgrade.MagicDamage * m_CurrentGameItemInfo.m_ItemUgrapeLevel;
				paramvalueAdd = paramRecord->ParamUpgrade.MagicDamage * IncreaseLevel;
				break;
			case ECharacterParam::HP:
				paramvalue = infoRecord->ItemEquipParam.HP + paramRecord->ParamUpgrade.HP * m_CurrentGameItemInfo.m_ItemUgrapeLevel;
				paramvalueAdd = paramRecord->ParamUpgrade.HP * IncreaseLevel;
				break;
			case ECharacterParam::Def:
				paramvalue = infoRecord->ItemEquipParam.Def + paramRecord->ParamUpgrade.Def * m_CurrentGameItemInfo.m_ItemUgrapeLevel;
				paramvalueAdd = paramRecord->ParamUpgrade.Def * IncreaseLevel;
				break;
			case ECharacterParam::MagicDef:
				paramvalue = infoRecord->ItemEquipParam.MagicDef + paramRecord->ParamUpgrade.MagicDef * m_CurrentGameItemInfo.m_ItemUgrapeLevel;
				paramvalueAdd = paramRecord->ParamUpgrade.MagicDef * IncreaseLevel;
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

void UUpgradeItemEquipmentPage::DecayExp(int64 TotalExp, TArray<FGameItemInfo>& GameItemInfoArray)
{
	GameItemInfoArray.Empty();
	
	UDataTable* UpgradeLevelOfMaterialTable = GetMgr(UTableMgr)->UpgradeLevelOfMaterialTable;
	if (nullptr == UpgradeLevelOfMaterialTable) return;

	TArray<FUpgradeLevelOfMaterialRecord*> allrows;
	UpgradeLevelOfMaterialTable->GetAllRows(FString(), allrows);

	int32 itemcount = 0;

	for (int i = allrows.Num() - 1; i >= 0; --i)
	{
		itemcount = TotalExp / (int64)(allrows[i]->expDecay);
		TotalExp = TotalExp % (int64)(allrows[i]->expDecay);

		if (itemcount > 0)
		{
			GameItemInfoArray.Emplace(FGameItemInfo(itemcount, allrows[i]->ItemReckey));
			GetMgr(UItemMgr)->AddItem(allrows[i]->ItemReckey, itemcount);
		}
	}
}
