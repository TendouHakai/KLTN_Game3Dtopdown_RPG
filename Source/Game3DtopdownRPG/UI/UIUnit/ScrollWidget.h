// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/GridPanel.h"
#include "ScrollWidget.generated.h"


UCLASS()
class GAME3DTOPDOWNRPG_API UScrollWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	UScrollWidget();
	virtual void CacheOwnUI() override;

	UFUNCTION(BlueprintCallable)
	virtual void AddWidgets(TArray<UBaseWidget*> widgets);

	UFUNCTION(BlueprintCallable)
	virtual void AddWidget(UBaseWidget* widget);

	UFUNCTION(BlueprintCallable)
	virtual void ClearAll();
protected:
	int32 CurRow;
	int32 CurCol;

	int32 TotalCol;
	int32 TotalRow;

	UGridPanel* GridContents;
};
