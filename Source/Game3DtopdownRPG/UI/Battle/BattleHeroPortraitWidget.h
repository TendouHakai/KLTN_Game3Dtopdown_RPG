// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIUnitWidget.h"
#include "BattleHeroPortraitWidget.generated.h"
  
class ABaseCharacter;
class UExpProgressBar;

UCLASS()
class GAME3DTOPDOWNRPG_API UBattleHeroPortraitWidget : public UUIUnitWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetInfo(ABaseCharacter* character);

	UFUNCTION(BlueprintCallable)
	void UpdateExpUI(int32 Exp);

protected:

	UExpProgressBar* expbar;

	ABaseCharacter* OwnerCharacter;
};
