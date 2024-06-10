// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "Game3DtopdownRPG/Define/StageStruct.h"
#include "StageMgr.generated.h"

struct FStageInfoRecord;
struct FChapterInfoRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UStageMgr : public USingleton
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void EndPlay() override;

	// info record
	FStageInfoRecord* GetStageInfoRecord(FName StageReckey);
	FChapterInfoRecord* GetChapterInfoRecord(FName ChapterReckey);

	TArray<int32> GetAllChapter();

	// get user data
	TArray<FGameStageInfo> GetStageArray() { return m_StageArray; }
	TArray<FGameStageInfo> GetStageArrayByChapter(int32 chapterReckey);

	// cheat
	void ClearStage(int32 stageReckey, int32 star);
	void UnlockStage(int32 stageReckey);
protected:
	TArray<FGameStageInfo> m_StageArray;
};
