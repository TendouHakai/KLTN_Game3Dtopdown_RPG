// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleVictoryWidget.h"
#include "Game3DtopdownRPG/GameMode/BattleGameMode.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/StageMgr.h"
#include "Game3DtopdownRPG/DataTable/StageTable.h"
#include "Game3DtopdownRPG/UI/WaitingWidget/LoadingWidget.h"

bool UBattleVictoryWidget::Initialize()
{
	bool isInitialize = Super::Initialize();
	if (isInitialize)
	{
		NextLevelBtn = GetOwnUI<UUIBaseButton>(FString(TEXT("UISquareButton_NexLevel")));
		BackBtn = GetOwnUI<UUIBaseButton>(FString(TEXT("UISquareButton_Back")));

		if (NextLevelBtn != nullptr)
		{
			NextLevelBtn->OnClicked_Delegate.Unbind();
			NextLevelBtn->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapNextLevel")));
		}
		if (BackBtn)
		{
			BackBtn->OnClicked_Delegate.Unbind();
			BackBtn->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapBacktoStartZone")));
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		USizeBox* widget = GetOwnUI<USizeBox>(FString::Printf(TEXT("SizeBox_star_%d"), i));
		if (widget)
		{
			widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			stars.Emplace(widget);
		}
	}

	return isInitialize;
}

void UBattleVictoryWidget::OnTapBacktoStartZone()
{
	ABattleGameMode* battlegamemode = Cast<ABattleGameMode>(GetGameModeAs(ABaseGameMode));

	if (battlegamemode != nullptr)
	{
		battlegamemode->BackToStartZone();
	}
}

void UBattleVictoryWidget::OnTapNextLevel()
{
	FStageInfoRecord* record = GetMgr(UStageMgr)->GetStageInfoRecord(FName(FString::FromInt(GetMgr(UStageMgr)->GetCurrentStage())));
	if (record == nullptr) return;
	
	FStageInfoRecord* NextRecord = GetMgr(UStageMgr)->GetStageInfoRecord(FName(FString::FromInt(record->NextStageReckey)));
	GetMgr(UStageMgr)->SetStage(record->NextStageReckey);

	ULoadingWidget* loadingWidget = Cast<ULoadingWidget>(GetMgr(UUIBaseMgr)->OpenUI(EUIName::LoadingWidget));
	if (loadingWidget != nullptr)
		loadingWidget->SetInfoScene(FName(NextRecord->MapName), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
}

void UBattleVictoryWidget::SetStar(int starcount)
{
	int count = stars.Num() >= starcount ? starcount : stars.Num();
	for (int starIndex = 0; starIndex < count; ++starIndex)
	{
		stars[starIndex]->SetVisibility(ESlateVisibility::Collapsed);
	}
}
