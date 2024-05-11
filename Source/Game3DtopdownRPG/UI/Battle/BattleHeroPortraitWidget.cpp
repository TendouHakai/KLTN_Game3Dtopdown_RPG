// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHeroPortraitWidget.h"
#include "../UIUnit/ExpProgressBar.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

void UBattleHeroPortraitWidget::NativeConstruct()
{
	Super::NativeConstruct();

	expbar = GetOwnUI<UExpProgressBar>(TEXT("ExpProgressBarBP"));
}

void UBattleHeroPortraitWidget::SetInfo(ABaseCharacter* character)
{
	OwnerCharacter = character;

	expbar->SetHeroExpInfo(character->GetHeroInfo());
}

void UBattleHeroPortraitWidget::UpdateExpUI(int32 Exp)
{
	//expbar->SetAddExp(Exp);
	expbar->SetHeroExpInfo(OwnerCharacter->GetHeroInfo());
}
