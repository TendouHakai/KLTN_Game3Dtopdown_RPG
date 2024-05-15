// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget.h"
#include "HeroEquipmentPage.generated.h"

struct FGameItemInfo;
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
	virtual void OnTapContainer(int32 rec_key, UInventoryEquipContainerWidget* Container) {}

	UFUNCTION(BlueprintCallable)
	virtual void SetHeroCharacter(ABaseCharacter* herocharacter);

protected:
	void UpdateChildItem(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildItemEquipment(UWidget* Child, int32 ChildDataIdx);

protected:
	// equipment
	TArray<UEquipmentSlotWidget*> EquipmentSlots;

	int32 m_CurrentItemIndex;
	TArray<FGameItemInfo> m_CurrentItemArray;

	UScrollWidget* ItemContainer_SCroll;
	UScrollWidget* ItemEquipmentContainer_SCroll;

	ABaseCharacter* character;
};
