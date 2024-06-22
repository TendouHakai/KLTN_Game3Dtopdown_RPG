// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/GameMode/BattleGameMode.h"

void UPauseMenu::CacheOwnUI()
{
	Super::CacheOwnUI();

	ResumeButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_ResumeButton"));
	BackButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Back"));
	SettingButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Setting"));

	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnResumeButton")));
	}

	if (nullptr != BackButton)
	{
		BackButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnBackButton")));
	}

	if (nullptr != SettingButton)
	{
		SettingButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnSettingButton")));
	}
}

bool UPauseMenu::Initialize()
{
	bool Initialize = Super::Initialize();
	if (Initialize)
	{
		CacheOwnUI();
	}
	return Initialize;
}

void UPauseMenu::OnResumeButton()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);	
	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}

void UPauseMenu::OnBackButton()
{
	ABattleGameMode* battlegamemode = Cast<ABattleGameMode>(GetGameModeAs(ABaseGameMode));

	if (battlegamemode != nullptr)
	{
		battlegamemode->BackToStartZone();
	}
}

void UPauseMenu::OnSettingButton()
{
	if (UIMgr != nullptr)
		UIMgr->OpenUI(EUIName::SettingMenu);
}
