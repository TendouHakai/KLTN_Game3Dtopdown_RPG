// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportLevel.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"

ATeleportLevel::ATeleportLevel()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATeleportLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleportLevel::SetIsPlayerInRange(bool isPlayerInRange)
{
	this->IsPlayerInRange = isPlayerInRange;
}

void ATeleportLevel::OnEnterLevel()
{
	if (IsPlayerInRange)
	{
		ABaseGameMode* gamemode = GetGameModeAs(ABaseGameMode);
		if (gamemode != nullptr)
		{
			gamemode->OpenReservedLevel(FName("Map01"), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
		}
	}
}


