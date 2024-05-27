// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "UpgradeItemEquipmentPage.generated.h"

class UScrollWidget;
struct FGameItemInfo;
struct FGameItemEquipmentInfo;
class UInventoryEquipContainerWidget;

UCLASS()
class GAME3DTOPDOWNRPG_API UUpgradeItemEquipmentPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	UFUNCTION()
	virtual void OnTapContainer(int32 rec_key, UInventoryEquipContainerWidget* Container);

protected:
	void UpdateChildMaterial(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildEquipmentItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildConsumeMaterial(UWidget* Child, int32 ChildDataIdx);
	
protected:
	TArray<UButton*> TabButtons;
	TArray<UImage*> TabForcuss;

	UScrollWidget* scrollEquipmentItem;
	UScrollWidget* scrollMaterial;
	UScrollWidget* scrollConsumeMaterial;

	TArray<FGameItemInfo> m_ItemUpgradeArray;
	TArray<FGameItemEquipmentInfo> m_ItemEquipmentArray;
};
