// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"

#include "InventoryContainerWidget.generated.h"

struct FItemInfoRecord;


UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryContainerWidget : public UUIUnitWidget
{
	GENERATED_BODY()

public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void SetInfo(FGameItemInfo* GameItemInfo, FItemInfoRecord* ItemInfoRecord);
	virtual void SetInfo(FGameItemInfo* GameItemInfo);

	void EmptyUI();

	UFUNCTION(BlueprintCallable)
	virtual void OnTap();

protected:
	void SetImageItem(FString ItemName);
	void SetTextCount(int32 count);
	void SetFrameBachground(EItemGrade grade);

protected:
	UImage* ImageEffect;
	UImage* ImageFrame;
	UImage* ImageBackground;
	UImage* ImageItem;
	UOverlay* OverlayCount;
	UTextBlock* TextCount;
	UWidgetAnimation* SelectAnimation;

	FGameItemInfo* gameItemInfo;
	FItemInfoRecord* itemInfoRecord;
};
