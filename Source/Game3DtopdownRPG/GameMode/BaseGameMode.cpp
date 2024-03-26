// Fill out your copyright notice in the Description page of Project Settings.
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"

#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"

void ABaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UIMgr = GetMgr(UUIBaseMgr);
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitInitialUI();
}

void ABaseGameMode::InitInitialUI()
{
	OnInitInitialUI();
}
