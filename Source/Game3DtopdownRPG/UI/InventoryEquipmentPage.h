// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "InventoryEquipmentPage.generated.h"

class UScrollWidget;
class UEquipmentSlotWidget;
class UUIBaseButton;
class UInventoryEquipContainerWidget;
class UEquipmentSlotWidget;
struct FGameItemEquipmentInfo;
class UTopMenuWidget;

UENUM(BlueprintType)
enum class EEquipItemTabCategory : uint8
{
	All = 0,
	Weapon,
	Shield,
	Shoe,
	Belt,
	Max
};

UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryEquipmentPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	// function for equip container
	UFUNCTION()
	void OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* container);

	UFUNCTION()
	void OnCtrlTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* container);

	// function for current equip slot
	UFUNCTION()
	void OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* container);

	UFUNCTION()
	void OnTapButtonSell();

	UFUNCTION(BlueprintCallable)
	void OnTapClose();

protected:
	void UpdateChildEquipmentContainer(UWidget* Child, int32 ChildDataIdx);

	UFUNCTION(BlueprintCallable)
	void SetTab(EEquipItemTabCategory tab);

	void SetCurrentEquipItem(FGameItemEquipmentInfo info);
	void UpdateDescriptionEquipItem();

protected:
	// UI
	// Tab Bar
	TArray<UButton*> TabButtons;
	TArray<UImage*> TabForcuss;
	UScrollWidget* ScrollWidget_EquipmentItem;

	// Decription
	UEquipmentSlotWidget* currentEquipSlot;
	UTextBlock* textGrade;
	UTextBlock* textName;
	UTextBlock* textDecription;
	TArray<UOverlay*> statInfos;
	TArray<UTextBlock*> statParamCurrent;
	TArray<UTextBlock*> statParamAdd;
	UTextBlock* textPrice;
	UUIBaseButton* buttonSell;

	// top menu widget
	UTopMenuWidget* TopMenu;

	// info
	FGameItemEquipmentInfo m_currentItemEquipInfo;
	TArray<FGameItemEquipmentInfo> m_currentEquipItemArray;
	EEquipItemTabCategory m_currenttab;
};
