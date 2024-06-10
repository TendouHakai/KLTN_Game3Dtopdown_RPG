// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "StageNaviButton.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FStageButtonTap_DelegateEx, int32, Output, UStageNaviButton*, Output02);

UCLASS()
class GAME3DTOPDOWNRPG_API UStageNaviButton : public UUIUnitWidget
{
	GENERATED_BODY()
public: 
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	virtual void SetInfo(int32 ChapterReckey, bool isfirst = false, bool islast = false);

	template<class T>
	void SetButtonEventEx(T* owner)
	{
		OwnerTap_DelegateEx.Unbind();
		OwnerTap_DelegateEx.BindDynamic(owner, &T::OnTapStageButton);
	}

	UFUNCTION(BlueprintCallable)
	void OnTapButton();

	void SetSelect(bool bSelect);

protected:
	// UI
	UImage* imageStage;
	UWidgetSwitcher* switcherSelect;

	// info
	int32 m_ChapterReckey;

	FStageButtonTap_DelegateEx OwnerTap_DelegateEx;
};
