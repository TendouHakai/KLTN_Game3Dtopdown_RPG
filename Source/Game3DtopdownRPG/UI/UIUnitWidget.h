// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "../Util/Managers/UIBaseMgr.h"

#include "UIUnitWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME3DTOPDOWNRPG_API UUIUnitWidget : public UBaseWidget
{
	GENERATED_BODY()
public:
	virtual bool IsValidWidget();

	UFUNCTION(BlueprintCallable, Category = "BaseWidget")
	void Show(bool isVisible);
protected:
	UUIBaseMgr* UIMgr;
};
