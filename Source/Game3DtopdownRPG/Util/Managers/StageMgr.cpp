// Fill out your copyright notice in the Description page of Project Settings.


#include "StageMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/DataTable/StageTable.h"
#include "Game3DtopdownRPG/Define/StageStruct.h"
#include "Game3DtopdownRPG/SavedStageConfig.h"
#include "TableMgr.h"

void UStageMgr::Init()
{
	Super::Init();

	m_StageArray.Empty();
	bool bSuccess = true;
	USavedStageConfig* config = USavedStageConfig::LoadStageCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		if (true == bSuccess)
		{
			m_StageArray = config->m_StageArray;
		}
		else
		{
			UDataTable* StageInfoTable = GetMgr(UTableMgr)->StageInfoTable;
			if (nullptr == StageInfoTable) return;

			TArray<FStageInfoRecord*> allrows;

			StageInfoTable->GetAllRows(FString(), allrows);

			for (int index = 0; index < allrows.Num(); ++index)
			{
				FGameStageInfo info;
				info.m_StageReckey = allrows[index]->StageReckey;
				info.m_bClear = false;
				info.m_bLock = false;
				info.m_star = 0;
				if (!m_StageArray.Contains(info))
				{
					m_StageArray.Emplace(info);
				}
			}
			if (m_StageArray.Num() > 0)
				UnlockStage(m_StageArray[0].m_StageReckey);
		}

	}
}

void UStageMgr::EndPlay()
{
	Super::EndPlay();

	bool bSuccess = true;
	USavedStageConfig* config = USavedStageConfig::LoadStageCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_StageArray = m_StageArray;
	}

	USavedStageConfig::SaveStageCfgToFile(config);
}

FStageInfoRecord* UStageMgr::GetStageInfoRecord(FName StageReckey)
{
	UDataTable* StageInfoTable = GetMgr(UTableMgr)->StageInfoTable;
	if (nullptr == StageInfoTable)
		return nullptr;

	FStageInfoRecord* StageInfoRecord = StageInfoTable->FindRow<FStageInfoRecord>(StageReckey, FString(""));

	if (nullptr == StageInfoRecord) return nullptr;

	return StageInfoRecord;
}

FChapterInfoRecord* UStageMgr::GetChapterInfoRecord(FName ChapterReckey)
{
	UDataTable* ChapterInfoTable = GetMgr(UTableMgr)->ChapterInfoTable;
	if (nullptr == ChapterInfoTable)
		return nullptr;

	FChapterInfoRecord* ChapterInfoRecord = ChapterInfoTable->FindRow<FChapterInfoRecord>(ChapterReckey, FString(""));

	if (nullptr == ChapterInfoRecord) return nullptr;

	return ChapterInfoRecord;
}

TArray<int32> UStageMgr::GetAllChapter()
{
	UDataTable* ChapterInfoTable = GetMgr(UTableMgr)->ChapterInfoTable;
	if (nullptr == ChapterInfoTable)
		return TArray<int32>();

	TArray<int32> chapterArray;
	TArray<FChapterInfoRecord*> allrows;

	ChapterInfoTable->GetAllRows(FString(), allrows);

	for (int chapterIndex = 0; chapterIndex < allrows.Num(); ++chapterIndex)
	{
		chapterArray.Add(allrows[chapterIndex]->ChapterReckey);
	}

	return chapterArray;
}

TArray<FGameStageInfo> UStageMgr::GetStageArrayByChapter(int32 chapterReckey)
{
	TArray<FGameStageInfo> StageArray;

	for (int32 stageIndex = 0; stageIndex < m_StageArray.Num(); ++stageIndex)
	{
		FStageInfoRecord* record = GetStageInfoRecord(FName(FString::FromInt(m_StageArray[stageIndex].m_StageReckey)));
		if (nullptr == record) continue;

		if(chapterReckey == record->ChapterReckey)
			StageArray.Emplace(m_StageArray[stageIndex]);
	}

	return StageArray;
}

void UStageMgr::SetStage(int32 stageReckey)
{
	m_currentStageReckey = stageReckey;
}

int32 UStageMgr::GetCurrentStage()
{
	return m_currentStageReckey;
}

void UStageMgr::ClearStage(int32 stageReckey, int32 star)
{
	if (stageReckey == 0) return;
	if (star == 0) return;

	// create data
	FGameStageInfo info;
	info.m_StageReckey = stageReckey;
	info.m_bClear = true;
	info.m_bLock = true;
	info.m_star = star;

	for (int stageIndex = 0; stageIndex < m_StageArray.Num(); ++stageIndex)
	{
		if (m_StageArray[stageIndex].m_StageReckey == stageReckey)
		{
			m_StageArray[stageIndex] = info;
			break;
		}
	}

	// unlock nextstage
	FStageInfoRecord* record = GetStageInfoRecord(FName(FString::FromInt(stageReckey)));
	UnlockStage(record->NextStageReckey);

	// save data
	bool bSuccess = true;
	USavedStageConfig* config = USavedStageConfig::LoadStageCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_StageArray = m_StageArray;
	}

	USavedStageConfig::SaveStageCfgToFile(config);
}

void UStageMgr::ClearCurrentStage(int32 star)
{
	if (star == 0) return;

	// create data
	FGameStageInfo info;
	info.m_StageReckey = m_currentStageReckey;
	info.m_bClear = true;
	info.m_bLock = true;
	info.m_star = star;

	for (int stageIndex = 0; stageIndex < m_StageArray.Num(); ++stageIndex)
	{
		if (m_StageArray[stageIndex].m_StageReckey == m_currentStageReckey)
		{
			m_StageArray[stageIndex] = info;
			break;
		}
	}

	// unlock nextstage
	FStageInfoRecord* record = GetStageInfoRecord(FName(FString::FromInt(m_currentStageReckey)));
	UnlockStage(record->NextStageReckey);

	// save data
	bool bSuccess = true;
	USavedStageConfig* config = USavedStageConfig::LoadStageCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_StageArray = m_StageArray;
	}

	USavedStageConfig::SaveStageCfgToFile(config);
}

void UStageMgr::UnlockStage(int32 stageReckey)
{
	if (stageReckey == 0) return;

	// create data
	FGameStageInfo info;
	info.m_StageReckey = stageReckey;
	info.m_bClear = false;
	info.m_bLock = true;

	for (int stageIndex = 0; stageIndex < m_StageArray.Num(); ++stageIndex)
	{
		if (m_StageArray[stageIndex].m_StageReckey == stageReckey)
		{
			m_StageArray[stageIndex] = info;
			break;
		}
	}

	// save data
	bool bSuccess = true;
	USavedStageConfig* config = USavedStageConfig::LoadStageCfgFromFile(bSuccess);
	if (nullptr != config)
	{
		config->m_StageArray = m_StageArray;
	}

	USavedStageConfig::SaveStageCfgToFile(config);
}
