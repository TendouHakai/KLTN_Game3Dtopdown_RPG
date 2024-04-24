// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "BattleSkillContainer.generated.h"


class ABaseCharacter;

UCLASS()
class GAME3DTOPDOWNRPG_API UBattleSkillContainer : public UUIUnitWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetSkillIndex(uint8 skillIdx) { this->SkillIndex = skillIdx; }

protected:
	uint8 SkillIndex = -1;
	ABaseCharacter* OwnerCharacter;

	UProgressBar* ProgressBarCooldown;
	UTextBlock* TextNumberCooldown;
};
