// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/Util/Managers/HeroMgr.h"
#include "Game3DtopdownRPG/GameMode/BattleGameMode.h"

void UPauseMenu::CacheOwnUI()
{
	Super::CacheOwnUI();

	ResumeButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_ResumeButton"));
	BackButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Back"));
	InstructButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Instruction"));
	SettingButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Setting"));
	QuitButton = GetOwnUI<UUIBaseButton>(TEXT("UISquareButton_Quit"));

	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnResumeButton")));
	}

	if (nullptr != BackButton)
	{
		BackButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnBackButton")));
	}

	if (nullptr != InstructButton)
	{
		InstructButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnInstructionButton")));
	}

	if (nullptr != SettingButton)
	{
		SettingButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnSettingButton")));
	}

	if (nullptr != QuitButton)
	{
		QuitButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnQuitButton")));
	}

	Update();
}

bool UPauseMenu::Initialize()
{
	bool Initialize = Super::Initialize();
	return Initialize;
}

void UPauseMenu::Update()
{
	Super::Update();

	if (GetMgr(UHeroMgr)->IsStartZone == true)
	{
		BackButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		BackButton->SetVisibility(ESlateVisibility::Visible);
	}
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

	GetMgr(UHeroMgr)->startPosition = EStartPosition::StartZone_Stage;

	if (battlegamemode != nullptr)
	{
		battlegamemode->BackToStartZone();
	}

	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}

void UPauseMenu::OnInstructionButton()
{
	if (UIMgr != nullptr)
		UIMgr->OpenUI(EUIName::InstructionWidget);

	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}

void UPauseMenu::OnSettingButton()
{
	if (UIMgr != nullptr)
		UIMgr->OpenUI(EUIName::SettingMenu);

	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}

void UPauseMenu::OnQuitButton()
{
	ABattleGameMode* battlegamemode = Cast<ABattleGameMode>(GetGameModeAs(ABaseGameMode));

	if (battlegamemode != nullptr)
	{
		battlegamemode->BackToMainMenu();
	}

	if (UIMgr != nullptr)
		UIMgr->CloseUI(this);
}
