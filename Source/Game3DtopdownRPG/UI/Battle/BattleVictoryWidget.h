// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "Game3DtopdownRPG/UI/UIUnit/UIBaseButton.h"
#include "BattleVictoryWidget.generated.h"


UCLASS()
class GAME3DTOPDOWNRPG_API UBattleVictoryWidget : public UUIWidget
{
	GENERATED_BODY()

public:  
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void OnTapBacktoStartZone();

	UFUNCTION(BlueprintCallable)
	void OnTapNextLevel();

private:
	UUIBaseButton* NextLevelBtn;
	UUIBaseButton* BackBtn;
};
