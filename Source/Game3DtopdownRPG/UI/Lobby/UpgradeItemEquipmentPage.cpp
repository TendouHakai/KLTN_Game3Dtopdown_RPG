// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeItemEquipmentPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/ItemMgr.h"
#include "Game3DtopdownRPG/UI/UIUnit/InventoryEquipContainerWidget.h"

void UUpgradeItemEquipmentPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	scrollEquipmentItem = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerItem"));
	if (nullptr != scrollEquipmentItem)
	{
		scrollEquipmentItem->InitUnit(GameMode);
		scrollEquipmentItem->ChildUpdateEvent.BindUObject(this, &UUpgradeItemEquipmentPage::UpdateChildEquipmentItem);
	}

	scrollConsumeMaterial = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ConsumeMaterials"));
	if (nullptr != scrollMaterial)
	{
		scrollConsumeMaterial->InitUnit(GameMode);
		scrollConsumeMaterial->ChildUpdateEvent.BindUObject(this, &UUpgradeItemEquipmentPage::UpdateChildConsumeMaterial);
	}
}

void UUpgradeItemEquipmentPage::Update()
{
	Super::Update();

	m_ItemEquipmentArray.Empty();
	m_ItemUpgradeArray.Empty();

	m_ItemEquipmentArray = GetMgr(UItemMgr)->GetItemEquipmentArray();
	//m_ItemUpgradeArray = GetMgr(UItemMgr)->GetItemArrayByItemType(EItemType::UpgradeEquipmentItem);

	if (nullptr != scrollEquipmentItem) scrollEquipmentItem->SetChildCount(m_ItemEquipmentArray.Num());
	//if (nullptr != scrollConsumeMaterial) scrollConsumeMaterial->SetChildCount(m_ItemEquipmentArray.Num());
}

void UUpgradeItemEquipmentPage::OnTapContainer(int32 rec_key, UInventoryEquipContainerWidget* Container)
{
}

void UUpgradeItemEquipmentPage::UpdateChildMaterial(UWidget* Child, int32 ChildDataIdx)
{

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

}
