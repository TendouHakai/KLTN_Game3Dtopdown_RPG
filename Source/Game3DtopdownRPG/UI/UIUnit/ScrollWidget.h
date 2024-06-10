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
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	virtual void ClearAll();

	virtual void SetChildCount(int32 InChildCount);

	virtual void Update() override;

	//void GetAllChidls();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ChildHeight = 232.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 VisibleRowCnt = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ChildCntPerRow = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<UUserWidget> ChildBP;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Vertical;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bAllowOverscroll = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) float RowFill = 0.0f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite) float ColumnFill = 0.0f;

	DECLARE_DELEGATE_TwoParams(FChildUpdateEvent, UWidget* /* Child */, int32 /* ChildDataIdx */);
	FChildUpdateEvent ChildUpdateEvent;
protected:
	int32 childcount = 0;

	UGridPanel* GridContents;
};
