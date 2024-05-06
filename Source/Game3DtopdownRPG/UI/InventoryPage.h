// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
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

	UFUNCTION()
	virtual void OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container);

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);
	bool IsItemInCategory(EItemCategory category);

	void UpdateDecriptionItem();

protected:
	TArray<UImage*> TabImagesForcus;

	EItemCategory m_CurItemType = EItemCategory::All;
	TArray<FGameItemInfo*> m_CurrentItemArray;

	UInventoryContainerWidget* CurrentSelectedItem;
	UScrollWidget* ItemContainer_SCroll;

	// Descruption Item Window
	UInventoryContainerWidget* ItemContainer;
	UTextBlock* textGradeItem;
	UTextBlock* textNameItem;
	URichTextBlock* textDecriptionItem;
	UTextBlock* textPriceItem;
};
