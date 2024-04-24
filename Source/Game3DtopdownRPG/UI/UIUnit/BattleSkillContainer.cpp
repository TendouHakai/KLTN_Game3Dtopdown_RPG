// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSkillContainer.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"

bool UBattleSkillContainer::Initialize()
{
	bool isInitialize = Super::Initialize();
	if (isInitialize)
	{

	}

	return isInitialize;
}

void UBattleSkillContainer::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressBarCooldown = GetOwnUI<UProgressBar>(TEXT("ProgressBar_Cooldown"));
	TextNumberCooldown = GetOwnUI<UTextBlock>(TEXT("TextBlock_Number"));
}

void UBattleSkillContainer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FNativeSkillInfo skillinfo = OwnerCharacter->GetNativeSkillInfo(SkillIndex);
	if (skillinfo.state == EBattleSkillState::Max)
	{
		
	}
}
