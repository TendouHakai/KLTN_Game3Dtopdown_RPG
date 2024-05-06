// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Components/Image.h"
#include "InventoryPage.generated.h"

class UInventoryContainerWidget;
class UScrollWidget;

UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnTapTabcategory(EItemCategory category);

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);
	bool IsItemInCategory(EItemCategory category);

protected:
	TArray<UImage*> TabImagesForcus;

	EItemCategory m_CurItemType = EItemCategory::All;
	TArray<FGameItemInfo*> m_CurrentItemArray;

	UInventoryContainerWidget* CurrentSelectedItem;
	UScrollWidget* ItemContainer_SCroll;
};
