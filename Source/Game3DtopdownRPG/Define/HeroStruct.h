// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game3DtopdownRPG/DataTable/HeroTable.h"
#include "HeroStruct.generated.h"


USTRUCT(BlueprintType)
struct FHeroExpInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int64 m_Exp;

	GENERATED_USTRUCT_BODY()

	FHeroExpInfo() { Reset(); }
	void Reset()
	{
		m_Exp = 0;
	}
};

USTRUCT(BlueprintType)
struct FHeroInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 HeroID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FHeroExpInfo HeroExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 m_Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FCharacterParam m_Param;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<int32> m_Equip;

	GENERATED_USTRUCT_BODY()

	FHeroInfo() : m_Level(1)
	{}
};