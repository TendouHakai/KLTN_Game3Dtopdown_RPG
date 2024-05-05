// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "InventoryContainerWidget.generated.h"

struct FGameItemInfo;
struct FItemInfoRecord;


UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryContainerWidget : public UUIUnitWidget
{
	GENERATED_BODY()

public:
	virtual void CacheOwnUI() override;

	virtual void SetInfo(FGameItemInfo* GameItemInfo, FItemInfoRecord* ItemInfoRecord);
	virtual void SetInfo(FGameItemInfo* GameItemInfo);

	UFUNCTION(BlueprintCallable)
	virtual void OnTap();

protected:
	void SetImageItem(FString ItemName);
	void SetTextCount(int32 count);

protected:
	UImage* ImageItem;
	UTextBlock* TextCount;
	UWidgetAnimation* SelectAnimation;

	FGameItemInfo* gameItemInfo;
	FItemInfoRecord* itemInfoRecord;
};
