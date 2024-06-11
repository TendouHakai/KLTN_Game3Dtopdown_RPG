// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "InventoryPage.generated.h"

class UInventoryContainerWidget;
class UScrollWidget;
class UUIBaseButton;
class UTopMenuWidget;

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

	UFUNCTION()
	virtual void OnTapSellItem();

	UFUNCTION()
	virtual void OnHandleSell();

	UFUNCTION()
	virtual void OnTapUseItem();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapClose();

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);
	bool IsItemInCategory(EItemCategory category);

	void UpdateDecriptionItem();

	void setCurrentSelectedItem(UInventoryContainerWidget* selectedItem);

protected:
	TArray<UImage*> TabImagesForcus;

	EItemCategory m_CurItemType = EItemCategory::All;
	TArray<FGameItemInfo> m_CurrentItemArray;

	UInventoryContainerWidget* CurrentSelectedItem;
	UScrollWidget* ItemContainer_SCroll;

	// Description Item Window
	UInventoryContainerWidget* ItemContainer;
	UTextBlock* textGradeItem;
	UTextBlock* textNameItem;
	URichTextBlock* textDecriptionItem;
	UTextBlock* textPriceItem;
	UUIBaseButton* SellButton;
	UUIBaseButton* UseButton;

	// top menu widget
	UTopMenuWidget* TopMenu;

	UVerticalBox* vertical_DesItem;
};
