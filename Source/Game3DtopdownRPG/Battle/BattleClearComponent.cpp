// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleClearComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game3DtopdownRPG/Util/Managers/UIBaseMgr.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/UI/Battle/BattleVictoryWidget.h"
#include "Game3DtopdownRPG/Util/Managers/StageMgr.h"
#include "Game3DtopdownRPG/GlobalGetter.h"


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

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ABaseCharacter* character = nullptr;
	if (PlayerCharacter != nullptr)
		character = Cast<ABaseCharacter>(PlayerCharacter);

	UBaseWidget* widget = nullptr;

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
		widget = Cast<UBattleVictoryWidget>(BattleGameMode->UIMgr->OpenUI(EUIName::BattleVictoryWidget));

		if (character != nullptr)
		{
			if (character->GetHealthRatio() >= 0.9f)
			{
				Cast<UBattleVictoryWidget>(widget)->SetStar(3);
				GetMgr(UStageMgr)->ClearCurrentStage(3);
			}
			else if (character->GetHealthRatio() >= 0.7f)
			{
				Cast<UBattleVictoryWidget>(widget)->SetStar(2);
				GetMgr(UStageMgr)->ClearCurrentStage(2);
			}
			else 
			{
				Cast<UBattleVictoryWidget>(widget)->SetStar(1);
				GetMgr(UStageMgr)->ClearCurrentStage(1);
			}
		}

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

