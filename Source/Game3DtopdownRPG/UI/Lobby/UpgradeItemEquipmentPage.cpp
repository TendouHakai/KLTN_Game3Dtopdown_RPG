// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeItemEquipmentPage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"

void UUpgradeItemEquipmentPage::CacheOwnUI()
{
	Super::CacheOwnUI();

	scrollEquipmentItem = GetOwnUI<UScrollWidget>(TEXT("ScrollWidget_ContainerItem"));
	if (nullptr != scrollEquipmentItem)
	{
		scrollEquipmentItem->InitUnit(GameMode);
		scrollEquipmentItem->ChildUpdateEvent.BindUObject(this, &UUpgradeItemEquipmentPage::UpdateChildUprgadeItem);
	}
}

void UUpgradeItemEquipmentPage::UpdateChildUprgadeItem(UWidget* Child, int32 ChildDataIdx)
{

}

void UUpgradeItemEquipmentPage::UpdateChildEquipmentItem(UWidget* Child, int32 ChildDataIdx)
{

}
