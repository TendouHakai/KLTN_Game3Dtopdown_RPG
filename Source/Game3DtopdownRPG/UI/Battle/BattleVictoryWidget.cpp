// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleVictoryWidget.h"
#include "Game3DtopdownRPG/GameMode/BattleGameMode.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"

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

}
