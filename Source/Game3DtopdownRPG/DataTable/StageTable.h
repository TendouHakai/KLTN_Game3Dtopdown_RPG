// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StageTable.generated.h"

USTRUCT(BlueprintType)
struct FStageInfoRecord : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 StageReckey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString strStage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ChapterReckey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString strChapter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 NextStageReckey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 NeedClearStageReckey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 NeedEnergy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 RewardExp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int64 RewardGold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<int32> RewardItems;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<int32> RewardItemCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 EnvironmentEffect;
};

USTRUCT(BlueprintType)
struct FChapterInfoRecord : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ChapterReckey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString StrChapter;
};