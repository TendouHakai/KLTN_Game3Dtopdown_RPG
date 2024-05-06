// Fill out your copyright notice in the Description page of Project Settings.
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"


void ABaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UIMgr = GetMgr(UUIBaseMgr);
	UIMgr->Init(this);
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitInitialUI();
}

void ABaseGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetRPGGameInstance()->EndPlayMgr();
}

void ABaseGameMode::InitInitialUI()
{
	OnInitInitialUI();
}

void ABaseGameMode::OpenReservedLevel(const FName NameLevel, const FString Options)
{
	UIMgr->CloseAllUI();
	UGameplayStatics::OpenLevel(GetWorld(), NameLevel, false, Options);
}
