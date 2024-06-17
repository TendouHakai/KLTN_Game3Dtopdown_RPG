// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "Components/RichTextBlock.h"
#include "Components/Overlay.h"
#include "HeroEquipmentPage.generated.h"

struct FGameItemInfo;
struct FGameItemEquipmentInfo;
class UScrollWidget;
class UInventoryEquipContainerWidget;
class UEquipmentSlotWidget;
class UItemSlotWidget;
class ABaseCharacter;
class UTopMenuWidget;

UENUM(BlueprintType)
enum class EEquipmentItemTabCategory : uint8
{
	All = 0,
	Weapon,
	Shield,
	Shoe,
	Belt,
	Max
};

UENUM(BlueprintType)
enum class EItemTabCategory : uint8
{
	All = 0,
	Common,
	Material,
	Potion,
	Max
};

UCLASS()
class GAME3DTOPDOWNRPG_API UHeroEquipmentPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	// function for equipment item
	UFUNCTION()
	virtual void OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container);

	UFUNCTION()
	void OnCtrlTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* container);

	UFUNCTION(BlueprintCallable)
	void OnCloseEquipItemDes() { ItemequipDesPopup->SetVisibility(ESlateVisibility::Collapsed); }

	// function for item
	UFUNCTION()
	virtual void OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container);

	UFUNCTION()
	virtual void OnCtrlTapInventoryContainer(int32 rec_key, UInventoryContainerWidget* Container);

	UFUNCTION(BlueprintCallable)
	void OnCloseItemDes() { ItemDesPopup->SetVisibility(ESlateVisibility::Collapsed); }

	// Function for slot equipmnet
	UFUNCTION()
	virtual void OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container);

	UFUNCTION()
	virtual void OnTapEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container);

	// Function for slot item
	UFUNCTION()
	virtual void OnDropItemSlot(int32 rec_key, UItemSlotWidget* Container);

	UFUNCTION()
	virtual void OnTapItemSlot(int32 rec_key, UItemSlotWidget* Container);

	UFUNCTION(BlueprintCallable)
	virtual void SetHeroCharacter(ABaseCharacter* herocharacter);

	UFUNCTION(BlueprintCallable)
	void OnTapTabEquipmentItemCategory(EEquipmentItemTabCategory tab);

	UFUNCTION(BlueprintCallable)
	void OnTapTabItemCategory(EItemTabCategory tab);

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx);
	void UpdateEquipmentSlots();
	void UpdateNormalEquipmentSlots();
	void UpdateHeroParams();

	void SetCurrentItemDes(FGameItemInfo info);
	void SetCurrentItemEquipDes(FGameItemEquipmentInfo info);

protected:
	// Tab Bar
	TArray<UButton*> TabEquipmentItemButtons;
	TArray<UImage*> TabEquipmentItemForcuss;
	EEquipmentItemTabCategory m_CurrentEquipmentItemCategory;

	TArray<UButton*> TabItemButtons;
	TArray<UImage*> TabItemForcuss;
	EItemTabCategory m_CurrentItemCategory;

	// equipment
	TArray<UEquipmentSlotWidget*> EquipmentSlots;

	TArray<FGameItemEquipmentInfo> m_CurrentItemEquipmentArray;
	UScrollWidget* ItemEquipmentContainer_SCroll;
	UVerticalBox* VerticalBoxItemEquipment;

	// Items
	TArray<UItemSlotWidget*> ItemSlots;

	TArray<FGameItemInfo> m_CurrentItemArray;
	UScrollWidget* ItemContainer_Scroll;
	UVerticalBox* VerticalBoxItem;

	// top menu widget
	UTopMenuWidget* TopMenu;

	ABaseCharacter* character;

	// Hero param
	TArray<UTextBlock*> HeroParam;

	// Pop up description item
	USizeBox* ItemDesPopup;
	UInventoryContainerWidget* m_currentItemWidget;
	UTextBlock* textGradeItem;
	UTextBlock* textNameItem;
	URichTextBlock* textDecriptionItem;

	// Pop up description item equipment
	USizeBox* ItemequipDesPopup;
	UEquipmentSlotWidget* m_currentEquipSlot;
	UTextBlock* textGrade;
	UTextBlock* textName;
	UTextBlock* textDecription;
	TArray<UOverlay*> statInfos;
	TArray<UTextBlock*> statParamCurrent;
	TArray<UTextBlock*> statParamAdd;
};
