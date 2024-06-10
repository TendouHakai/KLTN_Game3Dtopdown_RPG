// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Game3DtopdownRPG/Define/StageStruct.h"
#include "StageButton.generated.h"

UCLASS()
class GAME3DTOPDOWNRPG_API UStageButton : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void NativeConstruct() override;

	void SetInfo(FGameStageInfo info);

	UFUNCTION(BlueprintCallable)
	void OnTapButton();

protected:
	// UI
	UButton* button;
	UTextBlock* textStage;
	UImage* imageLock;
	UHorizontalBox* starBox;
	TArray<UImage*> stars;

	// info
	FGameStageInfo m_info;
};
