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

DECLARE_DYNAMIC_DELEGATE_TwoParams(FContainerTap_DelegateEx, int32, Output, UInventoryContainerWidget*, Output02);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FContainerTapUseSubtract_DelegateEx, int32, Output, UInventoryContainerWidget*, Output02);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FContainerDrop_DelegateEx, int32, Output, UInventoryContainerWidget*, Output02);

struct FItemInfoRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryContainerWidget : public UUIUnitWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void SetInfo(FGameItemInfo& GameItemInfo, FItemInfoRecord* ItemInfoRecord);
	UFUNCTION(BlueprintCallable)
	virtual void SetInfo(FGameItemInfo GameItemInfo);
	virtual void SetInfo(UInventoryContainerWidget* InventoryContainerWidget);

	void EmptyUI();

	UFUNCTION(BlueprintCallable)
	virtual void OnTap();

	UFUNCTION(BlueprintCallable)
	virtual void OnTapUseSubtract();

	UFUNCTION(BlueprintCallable)
	virtual void OnHover();

	UFUNCTION(BlueprintCallable)
	virtual void OnUnHover();

	UFUNCTION(BlueprintCallable)
	virtual void OnDropEvent(FGameItemInfo info);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FGameItemInfo GetGameItemInfo() { return gameItemInfo; }

	template<class T>
	void SetButtonEventEx(T* owner)
	{
		OwnerDelegateEx.Unbind();
		OwnerDelegateEx.BindDynamic(owner, &T::OnTapContainer);
	}

	template<class T>
	void SetButtonUseSubtractEventEx(T* owner)
	{
		OwnerUseSubtractDelegateEx.Unbind();
		OwnerUseSubtractDelegateEx.BindDynamic(owner, &T::OnTapUseSubtractContainer);
	}

	template<class T>
	void SetDropEventEx(T* owner)
	{
		OwnerDropDelefateEx.Unbind();
		OwnerDropDelefateEx.BindDynamic(owner, &T::OnDropInventoryContainer);
	}

	void SetUseCount(int32 count);
	void SetTextCountPerNumber(int32 number);
	void ShowInventoryLocation(bool IsShow);
public:
	FContainerTap_DelegateEx OwnerDelegateEx;
	FContainerTapUseSubtract_DelegateEx OwnerUseSubtractDelegateEx;
	FContainerDrop_DelegateEx OwnerDropDelefateEx;

	bool IsInteract = true;
protected:
	void SetImageItem(FString ItemName);
	void SetTextCount(int32 count);
	void SetFrameBackground(EItemGrade grade);
	void SetInventoryLocation(EInventoryLocation location);

	void HideEffect();

protected:
	UImage* ImageEffect;
	UImage* ImageFrame;
	UImage* ImageBackground;
	UImage* ImageItem;
	UOverlay* OverlayCount;
	UTextBlock* TextCount;
	UWidgetAnimation* SelectAnimation;
	UWidgetAnimation* ReleaseAnimation;

	// overlay use count
	UOverlay* OverlayUseCount;
	UTextBlock* TextUseCount;

	// overlay Inventory location
	UOverlay* OverlatInventoryLocation;
	UImage* imageinventoryLocation;

	FGameItemInfo gameItemInfo;
	FItemInfoRecord* itemInfoRecord;
};
