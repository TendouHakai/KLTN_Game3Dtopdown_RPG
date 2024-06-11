// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Game3DtopdownRPG/Define/StageStruct.h"
#include "Components/TextBlock.h"
#include "StagePage.generated.h"

class UScrollWidget;
class UStageNaviButton;
class UTopMenuWidget;

UCLASS()
class GAME3DTOPDOWNRPG_API UStagePage : public UUIWidget
{
	GENERATED_BODY()
public:
	virtual void CacheOwnUI() override;
	virtual void Update() override;

	// function for chapter button
	UFUNCTION()
	void OnTapStageButton(int32 reckey, UStageNaviButton* button);

	void UpdateChildStage(UWidget* Child, int32 ChildDataIdx);
	void UpdateChildChapter(UWidget* Child, int32 ChildDataIdx);

	UFUNCTION(BlueprintCallable)
	virtual void OnTapClose();

protected:
	void InitChapters();
	void SetCurrentChapter(int32 chapterReckey);

protected:
	// UI
	UScrollWidget* SCrollWidgetStage;
	UScrollWidget* SCrollWidgetChapter;
	UTextBlock* textNameChapter;

	// top menu widget
	UTopMenuWidget* TopMenu;

	// info
	int32 m_currentChapterReckey;
	TArray<FGameStageInfo> m_currentStageArray;
	TArray<int32> m_ChapterArray;
};
