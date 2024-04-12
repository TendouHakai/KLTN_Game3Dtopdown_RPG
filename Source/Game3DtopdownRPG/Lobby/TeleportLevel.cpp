// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportLevel.h"
#include "Game3DtopdownRPG/Game3DtopdownRPG.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/UI/WaitingWidget/LoadingWidget.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"

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

void ATeleportLevel::OnEnterLevel_Implementation()
{
	if (IsPlayerInRange)
	{
		ULoadingWidget* loadingWidget = Cast<ULoadingWidget>(GetMgr(UUIBaseMgr)->OpenUI(EUIName::LoadingWidget));
		if(loadingWidget != nullptr)
			loadingWidget->SetInfoScene(FName("Map01"), FString("?Game=/Game/Blueprints/Battle/BattleGameModeBP.BattleGameModeBP_C"));
	}
}


