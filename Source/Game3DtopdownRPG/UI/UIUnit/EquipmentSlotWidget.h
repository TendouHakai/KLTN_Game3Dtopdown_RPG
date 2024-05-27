
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/Image.h"
#include "Game3DtopdownRPG/DataTable/ItemTable.h"
#include "EquipmentSlotWidget.generated.h"

struct FGameItemInfo;
class UInventoryEquipContainerWidget;
class ABaseCharacter;

UCLASS()
class GAME3DTOPDOWNRPG_API UEquipmentSlotWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void SetHeroCharacter(ABaseCharacter* hero);

	UFUNCTION(BlueprintCallable)
	void EquipItemToSlot(FGameItemEquipmentInfo iteminfo);
	//void EmptyUI();

	virtual void Update() override;
protected:
	void setImageIcon();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UInventoryEquipContainerWidget* GetInventoryEquipment() { return inventoryEquipment; }
	
protected:
	UImage* imageIcon;
	UInventoryEquipContainerWidget* inventoryEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) EItemEquipPosition EquipmentPosition;
	ABaseCharacter* character;
};
