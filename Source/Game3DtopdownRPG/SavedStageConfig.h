// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Game3DtopdownRPG/Define/StageStruct.h"
#include "SavedStageConfig.generated.h"


UCLASS()
class GAME3DTOPDOWNRPG_API USavedStageConfig : public USaveGame
{
	GENERATED_BODY()
public:
	USavedStageConfig();

	UFUNCTION(BlueprintCallable, Category = "SavedStageConfig")
	static void SaveStageCfgToFile(USavedStageConfig* Cfg);

	UFUNCTION(BlueprintCallable, Category = "SavedStageConfig")
	static USavedStageConfig* LoadStageCfgFromFile(bool& bSuccess);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameStageInfo> m_StageArray;
};
