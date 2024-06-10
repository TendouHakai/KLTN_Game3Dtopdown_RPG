// Fill out your copyright notice in the Description page of Project Settings.


#include "StagePage.h"
#include "Game3DtopdownRPG/UI/UIUnit/ScrollWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/StageMgr.h"
#include "Game3DtopdownRPG/UI/UIUnit/StageNaviButton.h"
#include "Game3DtopdownRPG/UI/UIUnit/StageButton.h"
#include "Game3DtopdownRPG/DataTable/StageTable.h"

void UStagePage::CacheOwnUI()
{
	Super::CacheOwnUI();

	SCrollWidgetStage = GetOwnUI<UScrollWidget>(TEXT("ScrollWidgetBP_Stage"));
	if (nullptr != SCrollWidgetStage)
	{
		SCrollWidgetStage->InitUnit(GameMode);
		SCrollWidgetStage->ChildUpdateEvent.BindUObject(this, &UStagePage::UpdateChildStage);
	}
	SCrollWidgetChapter = GetOwnUI<UScrollWidget>(TEXT("ScrollWidgetBP_Chapter"));
	textNameChapter = GetOwnUI<UTextBlock>(TEXT("TextBlock_NameChapter"));

	InitChapters();
	SetCurrentChapter(m_ChapterArray[0]);
}

void UStagePage::Update()
{
	Super::Update();

	m_currentStageArray.Empty();
	m_currentStageArray = GetMgr(UStageMgr)->GetStageArrayByChapter(m_currentChapterReckey);
	if (SCrollWidgetStage != nullptr) SCrollWidgetStage->SetChildCount(m_currentStageArray.Num());
}

void UStagePage::OnTapStageButton(int32 reckey, UStageNaviButton* button)
{
	if (reckey == 0) return;
	SetCurrentChapter(reckey);
}

void UStagePage::UpdateChildStage(UWidget* Child, int32 ChildDataIdx)
{
	UStageButton* button = Cast<UStageButton>(Child);

	if (nullptr == button) return;
	if (!m_currentStageArray.IsValidIndex(ChildDataIdx)) return;

	FGameStageInfo info = m_currentStageArray[ChildDataIdx];
	button->SetInfo(info);
}

void UStagePage::UpdateChildChapter(UWidget* Child, int32 ChildDataIdx)
{
	UStageNaviButton* StageNaviButton = Cast<UStageNaviButton>(Child);

	if (nullptr == StageNaviButton) return;
	if (!m_ChapterArray.IsValidIndex(ChildDataIdx)) return;

	int32 ChapterReckey = m_ChapterArray[ChildDataIdx];

	if(ChildDataIdx == 0)
		StageNaviButton->SetInfo(ChapterReckey, true);
	else if(ChildDataIdx == m_ChapterArray.Num() - 1)
		StageNaviButton->SetInfo(ChapterReckey, false, true);
	else 
		StageNaviButton->SetInfo(ChapterReckey);

	StageNaviButton->SetButtonEventEx(this);

	if (m_currentChapterReckey == ChapterReckey)
		StageNaviButton->SetSelect(true);
	else
		StageNaviButton->SetSelect(false);
}

void UStagePage::InitChapters()
{
	m_ChapterArray = GetMgr(UStageMgr)->GetAllChapter();

	if (SCrollWidgetChapter != nullptr)
	{
		SCrollWidgetChapter->ChildCntPerRow = m_ChapterArray.Num();
		SCrollWidgetChapter->InitUnit(GameMode);
		SCrollWidgetChapter->ChildUpdateEvent.BindUObject(this, &UStagePage::UpdateChildChapter);
		SCrollWidgetChapter->SetChildCount(m_ChapterArray.Num());
	}
}

void UStagePage::SetCurrentChapter(int32 chapterReckey)
{
	m_currentChapterReckey = chapterReckey;

	FChapterInfoRecord* record = GetMgr(UStageMgr)->GetChapterInfoRecord(FName(FString::FromInt(chapterReckey)));
	if (nullptr == record) return;

	textNameChapter->SetText(FText::FromString(record->StrChapter));

	if (nullptr != SCrollWidgetChapter) SCrollWidgetChapter->SetChildCount(m_ChapterArray.Num());

	Update();
}
