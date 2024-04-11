// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleFailWidget.h"
#include "Game3DtopdownRPG/GameMode/BattleGameMode.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"

bool UBattleFailWidget::Initialize()
{
	bool isInitialize = Super::Initialize();
	if (isInitialize)
	{
		RepeatBtn = GetOwnUI<UUIBaseButton>(FString(TEXT("UISquareButton_Repeat")));
		BacktoStartZoneBtn = GetOwnUI<UUIBaseButton>(FString(TEXT("UISquareButton_BacktoStartZone")));

		if (RepeatBtn != nullptr)
		{
			RepeatBtn->OnClicked_Delegate.Unbind();
			RepeatBtn->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapReapeatBtn")));
		}

		if (BacktoStartZoneBtn != nullptr)
		{
			BacktoStartZoneBtn->OnClicked_Delegate.Unbind();
			BacktoStartZoneBtn->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapBackToBtn")));
		}
	}

	return isInitialize;
}

void UBattleFailWidget::OnTapReapeatBtn()
{
	ABattleGameMode* battlegamemode = Cast<ABattleGameMode>(GetGameModeAs(ABaseGameMode));

	if (battlegamemode != nullptr)
	{
		battlegamemode->RepeatBattle();
	}
}

void UBattleFailWidget::OnTapBackToBtn()
{
	ABattleGameMode* battlegamemode = Cast<ABattleGameMode>(GetGameModeAs(ABaseGameMode));

	if (battlegamemode != nullptr)
	{
		battlegamemode->BackToStartZone();
	}
}
