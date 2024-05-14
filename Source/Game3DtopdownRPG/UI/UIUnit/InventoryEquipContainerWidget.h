// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "InventoryEquipContainerWidget.generated.h"

struct FItemEquipmentInfoRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryEquipContainerWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void SetInfo(FGameItemInfo& GameItemInfo);
	virtual void SetInfo(FItemEquipmentInfoRecord* InventoryContainerWidget);
protected:
	void SetImageItem(FString ItemName);
	void SetTextCount(int32 count);
	void SetFrameBackground(EItemGrade grade);

protected:
	UImage* ImageFrame;
	UImage* ImageBack;
	UImage* ImageEffect;
	UImage* ImageItem;

	UTextBlock* textCount;

	FGameItemInfo gameItemInfo;
	FItemEquipmentInfoRecord* equipmentItemInfoRecord;
};
