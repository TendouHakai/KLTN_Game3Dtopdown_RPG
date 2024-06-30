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

void ABattleGameMode::BackToMainMenu()
{
	ULoadingWidget* loadingWidget = Cast<ULoadingWidget>(GetMgr(UUIBaseMgr)->OpenUI(EUIName::LoadingWidget));
	if (loadingWidget != nullptr)
		loadingWidget->SetInfoScene(FName("Login"), FString(""));
}

ABattleGameMode::ABattleGameMode()
{

}

ABattleGameMode::~ABattleGameMode()
{
}

void ABattleGameMode::InitGame(const FString& map_name, const FString& options, FString& error_message)
{
	Super::InitGame(map_name, options, error_message);

	GameModeState = EBattleGameModeState::None;
}

void ABattleGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsMatchInProgress())
	{
		switch (GameModeState)
		{
		case EBattleGameModeState::None:
			break;
		case EBattleGameModeState::BattleStart:
		{
			OnBeginProduction();
			
			GameModeState = EBattleGameModeState::PlayingBattle;
		}
			break;
		case EBattleGameModeState::PlayingBattle:
		{

		}
			break;
		case EBattleGameModeState::Max:
			break;
		default:
			break;
		}
	}
}

void ABattleGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABattleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ABattleGameMode::StartPlay()
{
	Super::StartPlay();

	GameModeState = EBattleGameModeState::BattleStart;
}

void ABattleGameMode::BeginPlay()
{
	Super::BeginPlay();
}
