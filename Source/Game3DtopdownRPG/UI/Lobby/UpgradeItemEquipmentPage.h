// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "UpgradeItemEquipmentPage.generated.h"

class UScrollWidget;
struct FGameItemInfo;
struct FGameEquipmentItemInfo;

UCLASS()
class GAME3DTOPDOWNRPG_API UUpgradeItemEquipmentPage : public UUIWidget
{
	GENERATED_BODY()
public:
	void CacheOwnUI() override;

protected:
	void UpdateChildUprgadeItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildEquipmentItem(UWidget* Child, int32 ChildDataIdx);
	
protected:
	TArray<UButton*> TabButtons;
	TArray<UImage*> TabForcuss;

	UScrollWidget* scrollEquipmentItem;
	UScrollWidget* scrollMaterial;

	TArray<FGameItemInfo> m_ItemUpgradeArray;
	TArray<FGameEquipmentItemInfo> m_ItemEquipmentArray;
};
