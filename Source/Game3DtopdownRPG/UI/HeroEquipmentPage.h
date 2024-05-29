// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "Components/TextBlock.h"
#include "HeroEquipmentPage.generated.h"

struct FGameItemInfo;
struct FGameItemEquipmentInfo;
class UScrollWidget;
class UInventoryEquipContainerWidget;
class UEquipmentSlotWidget;
class ABaseCharacter;

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

	UFUNCTION(BlueprintCallable)
	virtual void SetHeroCharacter(ABaseCharacter* herocharacter);

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx);
	void UpdateEquipmentSlots();
	void UpdateHeroParams();

protected:
	// equipment
	TArray<UEquipmentSlotWidget*> EquipmentSlots;

	int32 m_CurrentItemIndex;
	TArray<FGameItemEquipmentInfo> m_CurrentItemEquipmentArray;

	UScrollWidget* ItemContainer_SCroll;
	UScrollWidget* ItemEquipmentContainer_SCroll;

	ABaseCharacter* character;

	// Hero param
	TArray<UTextBlock*> HeroParam;
};
