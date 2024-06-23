// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_Page.h"
#include "Game3DtopdownRPG/UI/WaitingWidget/LoadingWidget.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/SavedUserConfig.h"

bool UMainMenu_Page::Initialize()
{
	bool IsInitialized = Super::Initialize();
	if (IsInitialized)
	{
		PlayButton = GetOwnUI<UUIBaseButton>(FString(TEXT("UISquareButton_Play")));
		OptionsButton = GetOwnUI<UUIBaseButton>(FString(TEXT("UISquareButton_Options")));
		QuitButton = GetOwnUI<UUIBaseButton>(FString(TEXT("UISquareButton_Quit")));

		PlayButton->OnClicked_Delegate.Unbind();
		PlayButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapPlayBtn")));

		OptionsButton->OnClicked_Delegate.Unbind();
		OptionsButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapOptionsBtn")));

		QuitButton->OnClicked_Delegate.Unbind();
		QuitButton->OnClicked_Delegate.BindUFunction(this, FName(TEXT("OnTapQuitBtn")));
	}

	return IsInitialized;
}

void UMainMenu_Page::Init()
{
	Super::Init();
}

void UMainMenu_Page::NativeConstruct()
{
	
}

void UMainMenu_Page::OnTapPlayBtn()
{
	bool bSuccess = true;
	USavedUserConfig* Config = USavedUserConfig::LoadUserCfgFromFile(bSuccess);
	if (nullptr != Config)
	{
		if (Config->IsFirstTime == true)
		{
			GetMgr(UUIBaseMgr)->OpenUI(EUIName::IntroSceenWidget);
			Config->IsFirstTime = false;
			USavedUserConfig::SaveUserCfgToFile(Config);
			return;
		}
	}
	ULoadingWidget* loadingWidget = Cast<ULoadingWidget>(GetMgr(UUIBaseMgr)->OpenUI(EUIName::LoadingWidget));
	if (loadingWidget != nullptr)
		loadingWidget->SetInfoScene(FName("StartZone"), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
	//GameMode->OpenReservedLevel(FName("StartZone"), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
}

void UMainMenu_Page::OnTapOptionsBtn()
{
	UIMgr->OpenUI(EUIName::SettingMenu);
}

void UMainMenu_Page::OnTapQuitBtn()
{

}

