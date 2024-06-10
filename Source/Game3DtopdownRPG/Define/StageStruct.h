// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StageStruct.generated.h"

USTRUCT(BlueprintType)
struct FGameStageInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_StageReckey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	bool m_bLock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	bool m_bClear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int32 m_star;

public:
	FGameStageInfo(int32 StageReckey = 0, bool bLock = false, bool bClear = false, int32 star = 0)
	{
		this->m_StageReckey = StageReckey;
		this->m_bLock = bLock;
		this->m_bClear = bClear;
		this->m_star = star;
	}

	bool operator==(const FGameStageInfo& Other) const
	{
		return (this->m_StageReckey == Other.m_StageReckey)
			&& (this->m_bLock == Other.m_bLock)
			&& (this->m_bClear == Other.m_bClear)
			&& (this->m_star == Other.m_star);
	}
};