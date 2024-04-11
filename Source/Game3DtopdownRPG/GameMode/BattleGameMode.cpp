// Fill out your copyright notice in the Description page of Project Settings.


#include "Game3DtopdownRPG/GameMode/BattleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"
#include "Game3DtopdownRPG/UI/WaitingWidget/LoadingWidget.h"

void ABattleGameMode::RepeatBattle()
{
	FString nameLev = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	OpenReservedLevel(FName(nameLev), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
}

void ABattleGameMode::BackToStartZone()
{
	ULoadingWidget* loadingWidget = Cast<ULoadingWidget>(GetMgr(UUIBaseMgr)->OpenUI(EUIName::LoadingWidget));
	if (loadingWidget != nullptr)
		loadingWidget->SetInfoScene(FName("StartZone"), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
}
