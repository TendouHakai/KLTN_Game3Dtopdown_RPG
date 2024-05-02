// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Singleton/Singleton.h"
#include "HeroBuffMgr.generated.h"

struct FBuffInfoRecord;

UCLASS()
class GAME3DTOPDOWNRPG_API UHeroBuffMgr : public USingleton
{
	GENERATED_BODY()
public:
	virtual FBuffInfoRecord* GetHeroBuffInfoRecord(int32 BuffType, int32 BuffCondition);
};
