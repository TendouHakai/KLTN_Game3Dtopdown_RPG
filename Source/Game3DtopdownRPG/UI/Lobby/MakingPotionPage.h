// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/ProgressBar.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "MakingPotionPage.generated.h"

class UScrollWidget;
class UInventoryContainerWidget;
class UUIBaseButton;
class UTopMenuWidget;

UENUM(BlueprintType)
enum class EMakePotionTabCategory : uint8
{
	PotionRecipe,
	MaterialRecipe,
	Max
};

UENUM(BlueprintType)
enum class EErrorMakingItemCode : uint8
{
	Count0 = 0,
	NotFindItem,
	NotHaveEnoughMaterial,
	Max
};

UCLASS()
class GAME3DTOPDOWNRPG_API UMakingPotionPage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	void UpdateChildPotionRecipe(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildMatrialRecipe(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildConsumeMatrial(UWidget* Child, int32 ChildDataIdx);

	// Function for tab Category
	UFUNCTION(BlueprintCallable)
	virtual void OnTapTabcategory(EMakePotionTabCategory category);

	// function for current inventory
	UFUNCTION()
	virtual void OnDropInventoryContainer(int32 rec_key, UInventoryContainerWidget* Container);

	// function for container
	UFUNCTION()
	void OnTapContainer(int32 rec_key, UInventoryContainerWidget* Container);

	// Function for button
	UFUNCTION(BlueprintCallable)
	virtual void OnTapAddCountItemButton();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapSubtractCountItemButton();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapMaxCountItemButton();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapMinCountItemButton();

	UFUNCTION(BlueprintCallable)
	virtual void OnValueChangeCountItem(int32 value);

	UFUNCTION(BlueprintCallable)
	virtual void OnTapMakePotionOrMaterial();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapClose();

protected:
	void SetCurrentItemToMake(FGameItemInfo info);
	void UpdateDecriptionCurrentItemToMake();
	void SetCountItemToMake(int32 count);

protected:
	TArray<UButton*> TabButtons;
	TArray<UImage*> TabForcuss;

	UScrollWidget* scrollPotionRecipe;
	UScrollWidget* scrollMaterialRecipe;
	UScrollWidget* scrollConsumeMaterial;

	TArray<FGameItemInfo> m_PotionRecipe;
	TArray<FGameItemInfo> m_MaterialRecipe;
	TArray<FGameItemInfo> m_ConsumeMaterial;

	EMakePotionTabCategory m_currentCategory;
	FGameItemInfo m_currentItemInfo;
	UInventoryContainerWidget* m_currentInventoryContainerWidget;

	// decription
	UTextBlock* textNameItem;
	UTextBlock* textCountItem;
	UTextBlock* textPrice;
	UTextBlock* textNumberConsumeMaterials;

	USlider* countItemSlider;
	UProgressBar* countItemProgressBar;

	// top menu widget
	UTopMenuWidget* TopMenu;

	UUIBaseButton* MakingPotionBtn;
};
