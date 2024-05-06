// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Game3DtopdownRPG\Battle\Buff\BuffStruct.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"

#include "BuffStateComponent.generated.h"

class UBaseBuff;

UCLASS()
class GAME3DTOPDOWNRPG_API UBuffStateComponent : public UUIUnitWidget
{
	GENERATED_BODY()

public:
	UBuffStateComponent();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void CacheOwnUI() override;
	virtual void Destroy(UUIBaseMgr* InUIManager) override;

	bool SetInfo(UBaseBuff* BaseBuff);
	virtual void SetInfo(const FHeroBuffInfo& HeroBuffInfo);

	UFUNCTION()	void UpdateBuffTimeInfo(UBaseBuff* BaseBuff);
	UFUNCTION() void UpdateInterruptInfo(UBaseBuff* BaseBuff);

	UFUNCTION(BlueprintImplementableEvent, Category = "BuffStateComponent")
	void InitIconOpacity();

	void ShowComponent(bool bShow);

	template<typename T>
	void AddSelectCallBack(T* BaseClass, void (T::* Infunc)(UBuffStateComponent*, bool))
	{
		OnSelectCallBack.Unbind();
		OnSelectCallBack.BindUObject(BaseClass, Infunc);
	}

	UFUNCTION(BlueprintCallable) void OnTapBuffIcon(bool bshow);
	FString GetBuffTextInfo() { return BuffInfoText; }

	FVector2D GetViewPortPosition() { return ViewPortPosition; }
	FVector2D GetLocalSize() { return LocalSize; }

protected:
	bool IsTimeShowException(UBaseBuff* BaseBuff);
	bool IsBlinkException(UBaseBuff* BaseBuff);

	virtual void SetBuffIcon(FString name);
protected:
	bool bShowBuffWidget;

	FString BuffInfoText;
	UTextBlock* BuffTime;
	UImage* BuffIcon;
	UImage* BuffLock;
	UWidgetAnimation* BuffStateAnim;

	FVector2D ViewPortPosition;
	FVector2D PixelPosition;
	FVector2D LocalSize;

	DECLARE_DELEGATE_TwoParams(FOnSelectCallBack, UBuffStateComponent*, bool);
	FOnSelectCallBack OnSelectCallBack;
};
