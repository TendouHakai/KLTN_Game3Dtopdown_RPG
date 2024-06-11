// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "HeroEquipmentPage.generated.h"

struct FGameItemInfo;
struct FGameItemEquipmentInfo;
class UScrollWidget;
class UInventoryEquipContainerWidget;
class UEquipmentSlotWidget;
class UItemSlotWidget;
class ABaseCharacter;

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

	UFUNCTION()
	virtual void OnTapEquipContainer(int32 rec_key, UInventoryEquipContainerWidget* Container) {}

	UFUNCTION()
	virtual void OnDropContainer(int32 rec_key, UInventoryEquipContainerWidget* Container) {}

	// Function for slot equipmnet
	UFUNCTION()
	virtual void OnDropEquipSlot(int32 rec_key, UEquipmentSlotWidget* Container);

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
	void UpdateHeroParams();

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

	ABaseCharacter* character;

	// Hero param
	TArray<UTextBlock*> HeroParam;
};
