// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/ProgressBar.h"
#include "ForgingEquipmentItemPage.generated.h"

class UScrollWidget;
class UEquipmentSlotWidget;
struct FGameItemEquipmentInfo;
struct FGameItemInfo;

UCLASS()
class GAME3DTOPDOWNRPG_API UForgingEquipmentItemPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	// Function for Equipment Container
	UFUNCTION()
	virtual void OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container);

	// Function for Equipment Slot
	UFUNCTION()
	virtual void OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container);

protected:
	void UpdateChildEquipmentItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildConsumeMaterials(UWidget* Child, int32 ChildDataIdx);

	void setCurrentForgingItem(FGameItemEquipmentInfo info);
	
	// UI
	void EmptyCurrentForgingItemUI();

protected:
	TArray<FGameItemEquipmentInfo> m_EquipmentItemRecipeArray;
	TArray<FGameItemInfo> m_ConsumeMaterialArray;

	UScrollWidget* ItemContainer_SCroll;
	UScrollWidget* ConsumeMaterials_SCroll;

	UEquipmentSlotWidget* m_currentForgingItem;
	UEquipmentSlotWidget* m_PreviousItem;

	UTextBlock* textName;
	UTextBlock* textCreateCountItem;
	USlider* sliderCountItem;
	UProgressBar* progressbarCountItem;
	UTextBlock* textPrice;
};
