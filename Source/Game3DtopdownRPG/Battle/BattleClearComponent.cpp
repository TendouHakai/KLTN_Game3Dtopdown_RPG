// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleClearComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"


// Sets default values for this component's properties
UBattleClearComponent::UBattleClearComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBattleClearComponent::BeginPlay()
{
	Super::BeginPlay();

	BattleGameMode = Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	BattleClearStep = EBattleClearStep::None;
}


// Called every frame
void UBattleClearComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (BattleClearStep)
	{
	case EBattleClearStep::None:
		break;
	case EBattleClearStep::GetItem:
		break;
	case EBattleClearStep::ReadyVictory:
		break;
	case EBattleClearStep::Failed:
		BattleGameMode->UIMgr->OpenUI(EUIName::BattleFailWidget);
		BattleClearStep = EBattleClearStep::None;
		break;
	case EBattleClearStep::Victory:
		BattleGameMode->UIMgr->OpenUI(EUIName::BattleVictoryWidget);
		BattleClearStep = EBattleClearStep::None;
		break;
	default:
		break;
	}
}

void UBattleClearComponent::SetTeleportWin(ATeleportLevel* teleport)
{
	this->TeleportWin = teleport;
}

void UBattleClearComponent::ShowTeleportWin()
{
	TeleportWin->SetActorHiddenInGame(false);
}

void UBattleClearComponent::SetBattleClearStep(EBattleClearStep step)
{
	this->BattleClearStep = step;
}

