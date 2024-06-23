// Fill out your copyright notice in the Description page of Project Settings.


#include "StageButton.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/DataTable/StageTable.h"
#include "Game3DtopdownRPG/UI/WaitingWidget/LoadingWidget.h"
#include "Game3DtopdownRPG/Util/Managers/StageMgr.h"
#include "Game3DtopdownRPG/Util/Managers/HeroMgr.h"

void UStageButton::CacheOwnUI()
{
	Super::CacheOwnUI();

	imageLock = GetOwnUI<UImage>(TEXT("Image_Lock"));
	textStage = GetOwnUI<UTextBlock>(TEXT("TextBlock_Stage"));
	starBox = GetOwnUI<UHorizontalBox>(TEXT("HorizontalBox_star"));

	if (stars.Num() <= 0)
	{
		for (int32 starIndex = 0; starIndex < 3; ++starIndex)
		{
			UImage* image = GetOwnUI<UImage>(FString::Printf(TEXT("star_%d"), starIndex));
			stars.Add(image);
		}
	}
}

void UStageButton::NativeConstruct()
{
	Super::NativeConstruct();
	CacheOwnUI();
}

void UStageButton::SetInfo(FGameStageInfo info)
{
	if (info.m_StageReckey == 0) return;
	m_info = info;
	
	FStageInfoRecord* record = GetMgr(UStageMgr)->GetStageInfoRecord(FName(FString::FromInt(m_info.m_StageReckey)));
	if (nullptr == record) return;

	textStage->SetText(FText::FromString(record->strStage));

	if (info.m_bLock)
	{
		imageLock->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		imageLock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (info.m_bClear)
	{
		starBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		for (int32 starIndex = 0; starIndex < info.m_star; ++starIndex)
		{
			stars[starIndex]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}

		for (int32 starIndex = info.m_star; starIndex < 3; ++starIndex)
		{
			stars[starIndex]->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		starBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UStageButton::OnTapButton()
{
	FStageInfoRecord* record = GetMgr(UStageMgr)->GetStageInfoRecord(FName(FString::FromInt(m_info.m_StageReckey)));
	if (nullptr == record) return;

	GetMgr(UHeroMgr)->IsStartZone = false;

	GetMgr(UStageMgr)->SetStage(record->StageReckey);

	ULoadingWidget* loadingWidget = Cast<ULoadingWidget>(GetMgr(UUIBaseMgr)->OpenUI(EUIName::LoadingWidget));
	if (loadingWidget != nullptr)
		loadingWidget->SetInfoScene(FName(record->MapName), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
}
