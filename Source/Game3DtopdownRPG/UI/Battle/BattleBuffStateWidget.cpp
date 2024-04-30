// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBuffStateWidget.h"
#include "BuffStateComponent.h"
#include "Game3DtopdownRPG/RPGGameInstance.h"
#include "Game3DtopdownRPG/GlobalGetter.h"
#include "Game3DtopdownRPG/GameMode/BaseGameMode.h"
#include "Game3DtopdownRPG/Battle/BaseCharacter.h"
#include "Game3DtopdownRPG/Battle/Buff/BaseBuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BaseDebuff.h"
#include "Game3DtopdownRPG/Battle/Buff/BuffControllerComponent.h"

UBattleBuffStateWidget::UBattleBuffStateWidget() : BattleCharacter(nullptr), PassiveBuffCount(0)
{
}

bool UBattleBuffStateWidget::Initialize()
{
	bool IsInitialized = Super::Initialize();
	if (IsInitialized)
	{
		BuffStateComponentArray.Empty();
		for (int i = 0; i < GetMaxBuffComponent(); ++i)
		{
			UBuffStateComponent* BuffStateComponent = GetOwnUI<UBuffStateComponent>(FString::Printf(TEXT("BuffStateComponent_%d"), i + 1));

			if (nullptr == BuffStateComponent)
				continue;

			BuffStateComponent->InitUnit(GameMode);
			BuffStateComponentArray.Add(BuffStateComponent);
		}
	}

	return IsInitialized;
}

void UBattleBuffStateWidget::SetBattleInfoContainer()
{

}

void UBattleBuffStateWidget::SetBattleCharacter(AActor* Actor)
{
	BattleActor = Actor;

	if (!Actor)
		return;

	if (false == IsValid(Actor))
		return;

	ABaseGameMode* BaseGameMode = GetGameModeAs(ABaseGameMode);
	if (BaseGameMode == nullptr)
		return;

	ClearBuffStateComponentInfo();

	CastActorToBaseCharacter();

	SetBuffInfo();
}

void UBattleBuffStateWidget::ClearBuffStateComponentInfo()
{
	PassiveBuffCount = 0;

	for (int i = 0; i < BuffStateComponentArray.Num(); ++i)
		HideBuffStateComponent(i);
}

void UBattleBuffStateWidget::UpdateBuffInfo()
{
	ABaseGameMode* BaseGameMode = GetGameModeAs(ABaseGameMode);
	if (BaseGameMode == nullptr)
		return;

	SetBuffInfo();
}

void UBattleBuffStateWidget::HideBuffStateComponent(int Idx)
{
	if (BuffStateComponentArray.Num() <= Idx)
		return;

	if (nullptr != BuffStateComponentArray[Idx])
		BuffStateComponentArray[Idx]->ShowComponent(false);
}

void UBattleBuffStateWidget::CastActorToBaseCharacter()
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(BattleActor);

	BattleCharacter = BaseCharacter;
}

void UBattleBuffStateWidget::SetBuffInfo()
{
	if (nullptr == BattleCharacter)
		return;

	if (false == IsValid(BattleCharacter))
		return;

	TArray<UBaseBuff*> BuffArray;
	BattleCharacter->HeroBuffController->FindHaveBuff(UBaseBuff::StaticClass(), BuffArray);

	TArray<UBaseBuff*> DeBuffArray;
	BattleCharacter->HeroBuffController->FindHaveBuff(UBaseDebuff::StaticClass(), DeBuffArray);

	int32 BuffCount = PassiveBuffCount;
	for (UBaseBuff* BaseBuff : BuffArray)
	{
		//if (true == DeBuffArray.Contains(BaseBuff))
		//	continue;

		//if (BaseBuff->IsPassiveBuff() || false == BaseBuff->IsActive()
		//	|| false == BaseBuff->IsHaveStateIcon())
		//	continue;

		if (true == SetBuffStateComponentInfo(BuffCount, BaseBuff))
			++BuffCount;

		if (BuffStateComponentArray.Num() <= BuffCount)
			return;
	}

	for (int i = BuffCount; i < BuffStateComponentArray.Num(); ++i)
		HideBuffStateComponent(i);
}

bool UBattleBuffStateWidget::SetBuffStateComponentInfo(int Idx, UBaseBuff* BaseBuff)
{
	if (BuffStateComponentArray.Num() <= Idx)
		return false;

	if (nullptr == BuffStateComponentArray[Idx])
		return false;

	if (false == BuffStateComponentArray[Idx]->SetInfo(BaseBuff))
		return false;

	BaseBuff->BindUpdateBuffInfoCallback(BuffStateComponentArray[Idx], &UBuffStateComponent::UpdateBuffTimeInfo);
	return true;
}
