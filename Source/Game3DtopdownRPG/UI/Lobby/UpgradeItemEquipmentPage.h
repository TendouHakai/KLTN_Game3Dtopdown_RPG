// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "UpgradeItemEquipmentPage.generated.h"

class UScrollWidget;
class UInventoryEquipContainerWidget;
class UEquipmentSlotWidget;
class UUIBaseButton;
class UTopMenuWidget;

UENUM(BlueprintType)
enum class EUgradeTabCategory : uint8
{
	EquipmentItem,
	UpgradeMaterial,
	Max
};

UCLASS()
class GAME3DTOPDOWNRPG_API UUpgradeItemEquipmentPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	// Function for Material Container
	UFUNCTION()
	virtual void OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container);

	UFUNCTION()
	virtual void OnTapUseSubtractContainer(int32 rec_key, UInventoryContainerWidget* Container);

	// Function for Equipment Container
	UFUNCTION()
	virtual void OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container);

	UFUNCTION()
	virtual void OnCtrlTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container);

	// Function for Equipment Slot
	UFUNCTION()
	virtual void OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container);

	// Function for tab Category
	UFUNCTION(BlueprintCallable)
	virtual void OnTapTabcategory(EUgradeTabCategory category);

	// Function for button
	UFUNCTION(BlueprintCallable)
	virtual void OnTapLevelUpBtn(EUgradeTabCategory category);

	UFUNCTION(BlueprintCallable)
	void OnTapCloseBtn();

protected:
	void UpdateChildMaterial(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildEquipmentItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildConsumeMaterial(UWidget* Child, int32 ChildDataIdx);

	void SetCurrentUpgradeEquipItem(FGameItemEquipmentInfo info);
	void UpdateDescriptionEquipItem();

	void setIncreaseUpgradeExp();

	void DecayExp(int64 TotalExp, TArray<FGameItemInfo>& GameItemInfoArray);
	
protected:
	TArray<UButton*> TabButtons;
	TArray<UImage*> TabForcuss;

	UScrollWidget* scrollEquipmentItem;
	UScrollWidget* scrollMaterial;
	UScrollWidget* scrollConsumeMaterial;

	TArray<FGameItemInfo> m_ItemUpgradeMaterialArray;
	TArray<FGameItemInfo> m_ConsumeMaterialArray;
	TArray<FGameItemEquipmentInfo> m_ItemEquipmentArray;

	// description 
	UTextBlock* textGrade;
	UTextBlock* textNameItem;
	UTextBlock* textCurrentLevel;
	UTextBlock* textLevelAdd;
	UTextBlock* textExpAdd;
	UTextBlock* textCurrentExp;
	UProgressBar* progressBarExp;
	TArray<UOverlay*> statInfos;
	TArray<UTextBlock*> statParamCurrent;
	TArray<UTextBlock*> statParamAdd;

	// button
	UUIBaseButton* LevUpBtn;

	// top menu widget
	UTopMenuWidget* TopMenu;

	// current category
	EUgradeTabCategory m_CurrentCategory;
	UEquipmentSlotWidget* m_CurrentEquipmentUpgradeItem;
	FGameItemEquipmentInfo m_CurrentGameItemInfo;

	int32 IncreaseLevel;
};
