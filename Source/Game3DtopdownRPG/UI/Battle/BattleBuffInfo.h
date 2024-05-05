// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UIWidget.h"
#include "BattleBuffInfo.generated.h"

class UTextBlock;
class UBuffStateComponent;

UCLASS()
class GAME3DTOPDOWNRPG_API UBattleBuffInfo : public UUIWidget
{
	GENERATED_BODY()

public:
	virtual void Init(ABaseGameMode* InGameMode);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void Destroy(UUIBaseMgr* InUIManager);
	UFUNCTION()	void ShowBuffInfo(UBuffStateComponent* BuffStateComponent, bool bShow);
	UFUNCTION()	void HideBuffInfo();
protected:
	UTextBlock* bufftextinfo;
	UWidgetAnimation* AnimHide;

	FTimerHandle HideTimer;
};
