// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Game3DtopdownRPG/Define/HeroStruct.h"

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

	UFUNCTION(BlueprintCallable)
	void SetSkillIndex(uint8 skillIdx) { this->SkillIndex = skillIdx; }

	UFUNCTION(BlueprintCallable)
	void SetSkillInfo(EHeroClass heroclass);

protected:
	uint8 SkillIndex = -1;

	UProgressBar* ProgressBarCooldown;
	UTextBlock* TextNumberCooldown;
};
