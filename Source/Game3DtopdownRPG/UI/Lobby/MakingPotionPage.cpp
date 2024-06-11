// Fill out your copyright notice in the Description page of Project Settings.


#include "MakingPotionPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryContainerWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "Game3DtopdownRPG/UI/UIUnit/TopMenuWidget.h"
#include "Game3DtopdownRPG/UI/MsgBox/MsgBoxReward.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"

void UMakingPotionPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	for (int tabindex = 0; tabindex < static_cast<int32>(EMakePotionTabCategory::Max); ++tabindex)
	{
		UButton* button = GetOwnUI<UButton>(FString::Printf(TEXT("Button_Tab_%d"), tabindex));
		UImage* imageforcus = GetOwnUI<UImage>(FString::Printf(TEXT("Image_forcus_%d"), tabindex));

		if (nullptr != button) TabButtons.Emplace(button);
		if (nullptr != imageforcus) TabForcuss.Emplace(imageforcus);
	}

	scrollPotionRecipe = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerPotion"));
	if (nullptr != scrollPotionRecipe)
	{
		scrollPotionRecipe->InitUnit(GameMode);
		scrollPotionRecipe->ChildUpdateEvent.BindUObject(this, &UMakingPotionPage::UpdateChildPotionRecipe);
	}

	scrollMaterialRecipe = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerMaterial"));
	if (nullptr != scrollMaterialRecipe)
	{
		scrollMaterialRecipe->InitUnit(GameMode);
		scrollMaterialRecipe->ChildUpdateEvent.BindUObject(this, &UMakingPotionPage::UpdateChildMatrialRecipe);
	}

	scrollConsumeMaterial = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ConsumeMaterial"));
	if (nullptr != scrollConsumeMaterial)
	{
		scrollConsumeMaterial->InitUnit(GameMode);
		scrollConsumeMaterial->ChildUpdateEvent.BindUObject(this, &UMakingPotionPage::UpdateChildConsumeMatrial);
	}

	m_currentInventoryContainerWidget = GetOwnUI<UInventoryContainerWidget>(TEXT("MyInventoryContainerWidget"));
	if (nullptr != m_currentInventoryContainerWidget)
	{
		m_currentInventoryContainerWidget->SetDropEventEx(this);
	}

	textNameItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesNameItemToMake"));
	if (textNameItem != nullptr) textNameItem->SetText(FText::FromString(""));
	textCountItem = GetOwnUI<UTextBlock>(TEXT("TextBlock_CountItemToMake"));
	textPrice = GetOwnUI<UTextBlock>(TEXT("TextBlock_DesPriceItemToMake"));
	countItemSlider = GetOwnUI<USlider>(TEXT("Slider_CountItem"));
	countItemProgressBar = GetOwnUI<UProgressBar>(TEXT("ProgressBar_CountItem"));

	MakingPotionBtn = GetOwnUI<UUIBaseButton>(TEXT("Button_MakingToPotion"));
	if (nullptr != MakingPotionBtn)
	{
		MakingPotionBtn->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapMakePotionOrMaterial")));
	}

	TopMenu = GetOwnUI<UTopMenuWidget>(TEXT("TopMenuWidgetBP"));
	if (nullptr != TopMenu) TopMenu->InitUnit(GameMode);

	OnTapTabcategory(EMakePotionTabCategory::PotionRecipe);
}

void UMakingPotionPage::Update()
{
	Super::Update();

	m_PotionRecipe.Empty();
	m_MaterialRecipe.Empty();

	m_PotionRecipe = GetMgr(UItemMgr)->GetAllItemRecipeByItemType(EItemType::Potion);
	m_MaterialRecipe = GetMgr(UItemMgr)->GetAllItemRecipeByItemType(EItemType::PotionMaterial);

	if (nullptr != scrollPotionRecipe) scrollPotionRecipe->SetChildCount(m_PotionRecipe.Num());
	if (nullptr != scrollMaterialRecipe) scrollMaterialRecipe->SetChildCount(m_MaterialRecipe.Num());
	if (nullptr != scrollConsumeMaterial) scrollConsumeMaterial->SetChildCount(m_ConsumeMaterial.Num());

	if (nullptr != TopMenu) TopMenu->Update();
}

void UMakingPotionPage::UpdateChildPotionRecipe(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_PotionRecipe.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_PotionRecipe[ChildDataIdx];

	InventoryContainer->SetInfo(info);

	InventoryContainer->SetButtonEventEx(this);
}

void UMakingPotionPage::UpdateChildMatrialRecipe(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_MaterialRecipe.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_MaterialRecipe[ChildDataIdx];

	InventoryContainer->SetInfo(info);
}

void UMakingPotionPage::UpdateChildConsumeMatrial(UWidget* Child, int32 ChildDataIdx)
{
	UInventoryContainerWidget* InventoryContainer = Cast<UInventoryContainerWidget>(Child);

	if (nullptr == InventoryContainer) return;
	if (!m_ConsumeMaterial.IsValidIndex(ChildDataIdx)) return;

	FGameItemInfo info = m_ConsumeMaterial[ChildDataIdx];

	InventoryContainer->SetInfo(info);
	InventoryContainer->SetTextCountPerNumber(info.m_ItemCount);
}

void UMakingPotionPage::OnTapTabcategory(EMakePotionTabCategory category)
{
	// hide all tab forcus
	for (int indextab = 0; indextab < TabForcuss.Num(); ++indextab)
	{
		TabForcuss[indextab]->SetVisibility(ESlateVisibility::Hidden);
	}
	// show current tab
	TabForcuss[static_cast<int32>(category)]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_currentCategory = category;

	switch (m_currentCategory)
	{
	case EMakePotionTabCategory::PotionRecipe:
		scrollPotionRecipe->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		scrollMaterialRecipe->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EMakePotionTabCategory::MaterialRecipe:
		scrollPotionRecipe->SetVisibility(ESlateVisibility::Collapsed);
		scrollMaterialRecipe->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case EMakePotionTabCategory::Max:
		break;
	default:
		break;
	}

	Update();
}

void UMakingPotionPage::OnDropInventoryContainer(int32 rec_key, UInventoryContainerWidget* Container)
{
	if (rec_key == 0) return;
	if (nullptr == Container) return;

	SetCurrentItemToMake(Container->GetGameItemInfo());
}

void UMakingPotionPage::OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container)
{
	if (rec_key == 0) return;
	if (nullptr == Container) return;

	SetCurrentItemToMake(Container->GetGameItemInfo());
}

void UMakingPotionPage::OnTapAddCountItemButton()
{
	if (m_currentItemInfo.m_ItemRecKey == 0) return;

	if (m_currentItemInfo.m_ItemCount >= countItemSlider->GetMaxValue())
		SetCountItemToMake(countItemSlider->GetMaxValue());
	else
		SetCountItemToMake(m_currentItemInfo.m_ItemCount + 1);
}

void UMakingPotionPage::OnTapSubtractCountItemButton()
{
	if (m_currentItemInfo.m_ItemRecKey == 0) return;

	if (m_currentItemInfo.m_ItemCount <= 0)
		SetCountItemToMake(0);
	else
		SetCountItemToMake(m_currentItemInfo.m_ItemCount - 1);
}

void UMakingPotionPage::OnTapMaxCountItemButton()
{
	if (m_currentItemInfo.m_ItemCount == 0) return;

	int32 maxCount = countItemSlider->GetMaxValue();

	for (int matIndex = 0; matIndex < m_ConsumeMaterial.Num(); ++matIndex)
	{
		FGameItemInfo info = GetMgr(UItemMgr)->FindItem(m_ConsumeMaterial[matIndex].m_ItemRecKey);
		int32 count = info.m_ItemCount / m_ConsumeMaterial[matIndex].m_ItemCount;
		if (maxCount > count) maxCount = count;
	}

	if (maxCount >= countItemSlider->GetMaxValue())
		SetCountItemToMake(countItemSlider->GetMaxValue());
	else if (maxCount <= 0)
		SetCountItemToMake(0);
	else
		SetCountItemToMake(maxCount);
}

void UMakingPotionPage::OnTapMinCountItemButton()
{
	if (m_currentItemInfo.m_ItemRecKey == 0) return;

	SetCountItemToMake(1);
}

void UMakingPotionPage::OnValueChangeCountItem(int32 value)
{
	SetCountItemToMake(value);
}

void UMakingPotionPage::OnTapMakePotionOrMaterial()
{
	int32 errorcode = -1;
	EResult result = GetMgr(UItemMgr)->MakeItem(m_currentItemInfo.m_ItemRecKey, m_currentItemInfo.m_ItemCount, errorcode);

	if (result == EResult::Success)
	{
		UUIBaseMsgBox* msg = UIMgr->OpenMsgBox(EUIMsgBoxType::Reward, TEXT("Success to make new item"), EUIMsgBoxBtnType::Confirm, this);
		if (Cast<UMsgBoxReward>(msg))
		{
			TArray<FGameItemInfo> arrays;
			arrays.Emplace(FGameItemInfo(m_currentItemInfo.m_ItemCount, m_currentItemInfo.m_ItemRecKey));
			Cast<UMsgBoxReward>(msg)->SetInfo(arrays);

			SetCountItemToMake(1);
		}
	}
	else if(result == EResult::Fail)
	{
		switch ((EErrorMakingItemCode)errorcode)
		{
		case EErrorMakingItemCode::Count0:
			UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, TEXT("Number of item created is 0"), EUIMsgBoxBtnType::Confirm, this);
			break;
		case EErrorMakingItemCode::NotFindItem:
			UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, TEXT("Not find item to make"), EUIMsgBoxBtnType::Confirm, this);
			break;
		case EErrorMakingItemCode::NotHaveEnoughMaterial:
			UIMgr->OpenMsgBox(EUIMsgBoxType::Basic, TEXT("Not enough Materials"), EUIMsgBoxBtnType::Confirm, this);
			break;
		default:
			break;
		}
	}

	Update();
}

void UMakingPotionPage::OnTapClose()
{
	if (UIMgr != nullptr)
		UIMgr->CloseScene();
}

void UMakingPotionPage::SetCurrentItemToMake(FGameItemInfo info)
{
	if (info.m_ItemRecKey == 0) return;
	m_currentItemInfo = info;
	m_currentInventoryContainerWidget->SetInfo(info);
	UpdateDecriptionCurrentItemToMake();
}

void UMakingPotionPage::UpdateDecriptionCurrentItemToMake()
{
	if (m_currentItemInfo.m_ItemRecKey == 0) return;

	FItemInfoRecord* record = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(m_currentItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;

	textNameItem->SetText(FText::FromString(record->DesName));
	SetCountItemToMake(1);
}

void UMakingPotionPage::SetCountItemToMake(int32 count)
{
	if (count < 0) return;
	m_currentItemInfo.m_ItemCount = count;

	FItemInfoRecord* record = GetMgr(UItemMgr)->GetItemInfoRecord(FName(FString::FromInt(m_currentItemInfo.m_ItemRecKey)));
	if (nullptr == record) return;

	textCountItem->SetText(FText::AsNumber(count));
	textPrice->SetText(FText::AsNumber(count * record->MakingGold));
	countItemSlider->SetValue(count);
	countItemProgressBar->SetPercent(count * 1.0f / countItemSlider->GetMaxValue());

	// update materials
	m_ConsumeMaterial.Empty();
	int32 maxMaterial = record->Materials.Num() > 4 ? 4 : record->Materials.Num();
	for (int matIndex = 0; matIndex < maxMaterial; ++matIndex)
	{
		FGameItemInfo info(record->MatCounts[matIndex]*count, record->Materials[matIndex]);
		m_ConsumeMaterial.Emplace(info);
	}

	if (nullptr != scrollConsumeMaterial) scrollConsumeMaterial->SetChildCount(m_ConsumeMaterial.Num());
}
