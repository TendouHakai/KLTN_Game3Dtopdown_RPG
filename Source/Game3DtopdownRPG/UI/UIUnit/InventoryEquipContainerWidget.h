// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Game3DtopdownRPG/Define/ItemStruct.h"
#include "InventoryEquipContainerWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FEquipmentContainerTap_DelegateEx, int32, Output, UInventoryEquipContainerWidget*, Output02);

struct FItemEquipmentInfoRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UInventoryEquipContainerWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void SetInfo(FGameItemEquipmentInfo& GameItemInfo);

	UFUNCTION(BlueprintCallable)
	virtual void SetInfo(int32 itemreckey);
	
	virtual void SetInfo(UInventoryEquipContainerWidget* InventoryContainerWidget);

	void EmptyUI();

	UFUNCTION(BlueprintCallable)
	virtual void OnTap();

	UFUNCTION(BlueprintCallable)
	virtual void OnHover();

	UFUNCTION(BlueprintCallable)
	virtual void OnUnHover();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FGameItemEquipmentInfo GetGameItemInfo() { return gameItemInfo; }

	template<class T>
	void SetButtonEventEx(T* owner)
	{
		OwnerDelegateEx.Unbind();
		OwnerDelegateEx.BindDynamic(owner, &T::OnTapEquipContainer);
	}

	bool IsInteract = true;
protected:
	void SetImageItem(FString ItemName);
	void SetTextUpgrapeLevel(int32 level);
	void SetFrameBackground(EItemGrade grade);

	UFUNCTION(BlueprintImplementableEvent)
	void setColorBackground(EItemGrade grade);

protected:
	UImage* ImageFrame;
	UImage* ImageBackground;
	UImage* ImageEffect;
	UImage* ImageItem;
	UOverlay* OverlayUpgradeLevel;
	UTextBlock* textUpgradeLevel;
	UWidgetAnimation* SelectAnimation;
	UWidgetAnimation* ReleaseAnimation;

	FGameItemEquipmentInfo gameItemInfo;
	FItemEquipmentInfoRecord* equipmentItemInfoRecord;

	FEquipmentContainerTap_DelegateEx OwnerDelegateEx;
};
