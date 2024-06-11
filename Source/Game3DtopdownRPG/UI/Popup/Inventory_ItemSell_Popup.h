// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/ProgressBar.h"
#include "Inventory_ItemSell_Popup.generated.h"

DECLARE_DELEGATE(FCallSellPopupFuncOnTap);

class UInventoryContainerWidget;
class UUIBaseButton;

UCLASS()
class GAME3DTOPDOWNRPG_API UInventory_ItemSell_Popup : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetInfo(FGameItemInfo iteminfo);

	UFUNCTION(BlueprintCallable)
	virtual void OnValueChangedSliderCountItem(int32 Value);

	UFUNCTION(BlueprintCallable)
	virtual void OnTapAddSellItemButton();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapSubtractSellItemButton();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapMinSellItemButton();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapMaxSellItemButton();

	UFUNCTION()
	virtual void OnTapCancelButton();

	UFUNCTION()
	virtual void OnTapSellButton();

protected:
	void SetSellItemCount(int32 count);

public:
	FCallSellPopupFuncOnTap HandleSell;

protected:
	FGameItemInfo GameItemInfo;
	int32 sellcount = 0;
	int32 sellPrice = 0;

	// Components
	UTextBlock* textNameItem;
	UTextBlock* textCountItem;
	UTextBlock* textSellCountItem;
	UTextBlock* textSellPriceItem;

	// Slider
	USlider* sliderCountItem;
	UProgressBar* progressbarCountItem;

	// button
	UUIBaseButton* SellButton;
	UUIBaseButton* CancelButton;
	UInventoryContainerWidget* InventoryContainer;
};
